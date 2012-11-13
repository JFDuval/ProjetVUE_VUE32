 /******************************************************************************
 * drive driver
 * by Pascal-Frédéric St-Laurent - 08/11/2012
 * ****************************************************************************/

#include "drive.h"

void DriveEnable(DRIVE_STATUS *pDrives, unsigned char ucDriveIndex)
{
    if(pDrives[ucDriveIndex].ucIsEnable != DRIVE_ENABLE)
    {
        pDrives[ucDriveIndex].ucIsEnable = DRIVE_ENABLE;

        //Safety start with a command at zero
        pDrives[ucDriveIndex].ufMotorCommand = 0;

        DRIVE_MSG driveMessage;
        driveMessage.address = pDrives[ucDriveIndex].unBaseAddr;
        driveMessage.ucType = DRIVE_FRAME_ENABLE_DISABLE;
        driveMessage.dataLenght = 8;
        driveMessage.data[0] = pDrives[ucDriveIndex].ucIsEnable;

        //Send to CAN network interface
        CanNETSACTxMessage(&driveMessage, D_CAN2);
    }

    return;
}

void DriveDisable(DRIVE_STATUS *pDrives, unsigned char ucDriveIndex)
{
    if(pDrives[ucDriveIndex].ucIsEnable != DRIVE_DISABLE)
    {
        pDrives[ucDriveIndex].ucIsEnable = DRIVE_DISABLE;

        //Safety stop with a command at zero
        pDrives[ucDriveIndex].ufMotorCommand = 0;
        DriveTXCmd(pDrives+ucDriveIndex);

        DRIVE_MSG driveMessage;
        driveMessage.address =pDrives[ucDriveIndex].unBaseAddr;
        driveMessage.ucType = DRIVE_FRAME_ENABLE_DISABLE;
        driveMessage.dataLenght = 8;
        driveMessage.data[0] = pDrives[ucDriveIndex].ucIsEnable;

        //Send to CAN network interface
        CanNETSACTxMessage(&driveMessage, D_CAN2);
    }
}

/* fCommandMotor unit depends on the drive configuration. Basically, this funtion must received torque command in Newton/Meter or speed command in rotation per minute (RPM)*/
void DriveStateMachine(DRIVE_STATUS *pDrives, unsigned char ucDriveIndex, float fCommandMotor, short usUnscaledTemp)
{
    if(!pDrives[ucDriveIndex].ucIsEnable)
        return;
    
    //Error Handler
    if(pDrives[ucDriveIndex].ucIsOnEmergency)
    {
        DrivesEmergencyModeHandler(pDrives);
    }
    //Check if a new error happened
    else if(pDrives[ucDriveIndex].usStatus != NO_ERROR)
    {
        //Stop each motor
        DrivesEmergencyStop(pDrives);
        return;
    }

    pDrives[ucDriveIndex].ufMotorCommand = fCommandMotor;
    pDrives[ucDriveIndex].usUnscaledMotorTemp = usUnscaledTemp;

    //Update cmd on the drive side
    DriveTXCmd(pDrives+ucDriveIndex);
}

void DrivesEmergencyStop(DRIVE_STATUS *pDrives)
{
    unsigned i;

    for(i = 0; i<NBROFDRIVE; i++)
    {
        //Send com pDrive[i].ufCommandMotor = 0;
        pDrives[i].ufMotorCommand = 0;
        DriveTXCmd(pDrives+i);
        //Mark drive as under emergency
        pDrives[i].ucIsOnEmergency = 1;
    }
    return;
}

void DrivesEmergencyModeHandler(DRIVE_STATUS *pDrives)
{
    unsigned char ucErrorFound = 0;
    unsigned char i =0;
    //Verify if the every drive hasn't an error
    for(i = 0; i<NBROFDRIVE; i++)
    {
        if(pDrives[i].usStatus != NO_ERROR)
            ucErrorFound = 1;
    }

    //If an error is recorded on a drive
    if(ucErrorFound)
        return;

    //All drives will be released for emergency state
    for(i = 0; i<NBROFDRIVE; i++)
    {
        pDrives[i].ucIsOnEmergency = 0;
    }
}
void DriveTXCmd(DRIVE_STATUS *pDrive)
{
    DRIVE_MSG driveMessage;
    driveMessage.address = pDrive->unBaseAddr;
    driveMessage.ucType = DRIVE_FRAME_CONTROL;
    driveMessage.dataLenght = 8;

    //Scale fonct
    if(pDrive->ucSelectedMode == TORQUE_MODE || pDrive->ucSelectedMode == EV_MODE)
        pDrive->usMotorCommand = ScaleTorqueValue(pDrive->ufMotorCommand);
    else if(pDrive->ucSelectedMode == SPEED_MODE)
        pDrive->usMotorCommand = ScaleSpeedValue(pDrive->ufMotorCommand);
    else
        return;

    driveMessage.data[0] = (unsigned char)((pDrive->usMotorCommand >> 8) & 0x00FF);
    driveMessage.data[1] = (unsigned char)(pDrive->usMotorCommand & 0x00FF);

    //Motor Selector
    driveMessage.data[2] = pDrive->ucSelectedMode;

    //Power Limit
    driveMessage.data[4] = pDrive->ucPowerLimit;

    //Temperature
    pDrive->usScaledMotorTemp = ScaleMotorTempValue(pDrive->usUnscaledMotorTemp);
    driveMessage.data[5] = (unsigned char)((pDrive->usScaledMotorTemp >> 8) & 0x00FF);
    driveMessage.data[6] = (unsigned char)(pDrive->usScaledMotorTemp & 0x00FF);


    //Send to CAN network interface
    CanNETSACTxMessage(&driveMessage, D_CAN2);
}

void DriveRXCmd(DRIVE_MSG *pMessage, DRIVE_STATUS *pDrives)
{
    unsigned char i = 0;
    char ucDriveIndex = -1;

    //Validate if there is a valid BaseID
    for(i = 0; i<NBROFDRIVE; i++)
    {
        if(pDrives[i].unBaseAddr == pMessage->address)
        {
            ucDriveIndex = i;
        }
    }

    //Returning if no drive has been found
    if(ucDriveIndex == -1)
        return;

    //payload parser
    switch(pMessage->ucType)
    {
        case DRIVE_FRAME_INFO1:
            pDrives[ucDriveIndex].usMotorSpeed = (pMessage->data[0] << 8) & 0xFF00;
            pDrives[ucDriveIndex].usMotorSpeed |= (pMessage->data[1]);
            pDrives[ucDriveIndex].usBatteryVoltage  = (pMessage->data[2] << 8) & 0xFF00;
            pDrives[ucDriveIndex].usBatteryVoltage |= (pMessage->data[3]);
            pDrives[ucDriveIndex].usMotorCurrent = (pMessage->data[4] << 8) & 0xFF00;
            pDrives[ucDriveIndex].usMotorCurrent |= (pMessage->data[5]);
            pDrives[ucDriveIndex].usStatus = (pMessage->data[6] << 8) & 0xFF00;
            pDrives[ucDriveIndex].usStatus |=  (pMessage->data[7]);
            break;
        case DRIVE_FRAME_INFO2:
            pDrives[ucDriveIndex].ucMotorTemp = pMessage->data[0];
            pDrives[ucDriveIndex].ucControllerTemp = pMessage->data[1];
            pDrives[ucDriveIndex].usDPotentiometer = (pMessage->data[2] << 8) & 0xFF00;
            pDrives[ucDriveIndex].usDPotentiometer |= pMessage->data[3];
            pDrives[ucDriveIndex].usAnalogIn = (pMessage->data[4] << 8) & 0xFF00;
            pDrives[ucDriveIndex].usAnalogIn |= pMessage->data[5];
            pDrives[ucDriveIndex].usBatteryCurrent = (pMessage->data[6] << 8) & 0xFF00;
            pDrives[ucDriveIndex].usBatteryCurrent |= pMessage->data[7];
            break;
    }
}

unsigned short ScaleTorqueValue(float fValue)
{
    return (unsigned short)(fValue*TORQUE_SCALING_K+TORQUE_SCALING_B);
}

unsigned short ScaleSpeedValue(float fValue)
{
    return (unsigned short)(fValue*SPEED_SCALING_K+SPEED_SCALING_B);
}

unsigned short ScaleMotorTempValue(unsigned short usValue)
{
    return  TEMP_CONVERTING_OFFSET+usValue;
}

void PoolingDrive(DRIVE_STATUS *pDrives, unsigned char ucDriveIndex, unsigned char usCommandType)
{
    DRIVE_MSG driveMessage;

    driveMessage.RTR = usCommandType > 1 ? 1 : 0 ;
    driveMessage.address = pDrives[ucDriveIndex].unBaseAddr;
    driveMessage.dataLenght = 8;
    driveMessage.ucType = usCommandType;
    
    CanNETSACTxMessage(&driveMessage, D_CAN2);
}