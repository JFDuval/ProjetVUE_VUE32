 /******************************************************************************
 * drive driver
 * by Pascal-Frédéric St-Laurent - 08/11/2012
 * ****************************************************************************/

#include "drive.h"
#include <math.h>

void DriveEnable(DRIVE_STATUS *pDrives, unsigned char ucDriveIndex)
{
    /*if(pDrives[ucDriveIndex].ucIsEnable != DRIVE_ENABLE)
    {*/
        pDrives[ucDriveIndex].ucIsEnable = DRIVE_ENABLE;

        //Safety start with a command at zero
        pDrives[ucDriveIndex].ufMotorCommand = 0;

        DRIVE_MSG driveMessage;
        driveMessage.address = pDrives[ucDriveIndex].unBaseAddrRead;
        driveMessage.ucType = DRIVE_FRAME_ENABLE_DISABLE;
        driveMessage.dataLenght = 8;
        //Must be always set to zero
        driveMessage.RTR = 0;
        driveMessage.data[0] = pDrives[ucDriveIndex].ucIsEnable;
        driveMessage.data[1] = 0;
        driveMessage.data[2] = 0;
        driveMessage.data[3] = 0;
        driveMessage.data[4] = 0;
        driveMessage.data[5] = 0;
        driveMessage.data[6] = 0;
        driveMessage.data[7] = 0;

        //Send to CAN network interface
        CanNETSACTxMessage(&driveMessage, D_CAN2);
}

void DriveDisable(DRIVE_STATUS *pDrives, unsigned char ucDriveIndex)
{
    /*if(pDrives[ucDriveIndex].ucIsEnable != DRIVE_DISABLE)
    {*/
        pDrives[ucDriveIndex].ucIsEnable = DRIVE_DISABLE;

        //Safety stop with a command at zero
        pDrives[ucDriveIndex].ufMotorCommand = 0;
        DriveTXCmd(pDrives+ucDriveIndex);

        DRIVE_MSG driveMessage;
        driveMessage.address =pDrives[ucDriveIndex].unBaseAddrRead;
        driveMessage.ucType = DRIVE_FRAME_ENABLE_DISABLE;
        driveMessage.RTR = 0;
        driveMessage.dataLenght = 8;
        driveMessage.data[0] = pDrives[ucDriveIndex].ucIsEnable;
        driveMessage.data[1] = 0;
        driveMessage.data[2] = 0;
        driveMessage.data[3] = 0;
        driveMessage.data[4] = 0;
        driveMessage.data[5] = 0;
        driveMessage.data[6] = 0;
        driveMessage.data[7] = 0;

        //Send to CAN network interface
        CanNETSACTxMessage(&driveMessage, D_CAN2);
    //}
}

/* fCommandMotor unit depends on the drive configuration. Basically, this funtion must received torque command in Newton/Meter or speed command in rotation per minute (RPM)*/
void DriveStateMachine(DRIVE_STATUS *pDrives, unsigned char ucDriveIndex, float fCommandMotor, short usUnscaledTemp)
{
    if(!pDrives[ucDriveIndex].ucIsEnable)
        return;
    
    //Error Handler
    if(DrivesError(pDrives))
            return;

    if(pDrives[ucDriveIndex].ucIsInvert)
        pDrives[ucDriveIndex].ufMotorCommand = -fCommandMotor;
    else
        pDrives[ucDriveIndex].ufMotorCommand = fCommandMotor;
    pDrives[ucDriveIndex].usMotorTempADC = usUnscaledTemp;

    //Update cmd on the drive side
    DriveTXCmd(pDrives+ucDriveIndex);
}

char DrivesError(DRIVE_STATUS *pDrives)
{
    unsigned char ucErrorFound = 0;
    unsigned char i =0;
    //Verify if the every drive hasn't an error
    for(i = 0; i<NBROFDRIVE; i++)
    {
        if(pDrives[i].ucStatus != NO_ERROR)
        {
            ucErrorFound = 1;
        }
    }

    for(i = 0; i<NBROFDRIVE; i++)
    {
        pDrives[i].ucIsOnEmergency = ucErrorFound;
    }

    //If an error is recorded on a drive
    if(ucErrorFound)
        return 1;
    //Release system
    return 0;
}
void DriveTXCmd(DRIVE_STATUS *pDrive)
{
    DRIVE_MSG driveMessage;
    driveMessage.address = pDrive->unBaseAddrRead;
    driveMessage.ucType = DRIVE_FRAME_CONTROL;
    driveMessage.dataLenght = 8;
    driveMessage.RTR = 0;

    //Scale fonct
    if(pDrive->ucSelectedMode == TORQUE_MODE || pDrive->ucSelectedMode == EV_MODE)
        pDrive->usMotorCommand = ScaleTorque(pDrive->ufMotorCommand);
    else if(pDrive->ucSelectedMode == SPEED_MODE)
        pDrive->usMotorCommand = ScaleSpeed(pDrive->ufMotorCommand);
    else
        return;

    driveMessage.data[0] = (unsigned char)((pDrive->usMotorCommand >> 8) & 0x00FF);
    driveMessage.data[1] = (unsigned char)(pDrive->usMotorCommand & 0x00FF);

    //Motor Selector
    driveMessage.data[2] = pDrive->ucSelectedMode;

    //Power Limit
    driveMessage.data[3] = pDrive->ucPowerLimit;

    //Temperature
    driveMessage.data[4] = (unsigned char)((pDrive->usMotorTempADC >> 8) & 0x00FF);
    driveMessage.data[5] = (unsigned char)(pDrive->usMotorTempADC & 0x00FF);
    driveMessage.data[6] = 0;
    driveMessage.data[7] = 0;


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
        if(pDrives[i].unBaseAddrWrite == pMessage->address)
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
            pDrives[ucDriveIndex].nMotorSpeed = UnScaleSpeed(((pMessage->data[0] << 8) & 0xFF00)| pMessage->data[1]);
            pDrives[ucDriveIndex].unBatteryVoltage = UnScaleVoltage(((pMessage->data[2] << 8) & 0xFF00)| pMessage->data[3]);
            pDrives[ucDriveIndex].unMotorCurrent = UnScaleRMSCurrent(((pMessage->data[4] << 8) & 0xFF00)| pMessage->data[5]);
            pDrives[ucDriveIndex].ucStatus =  pMessage->data[7];
            break;
        case DRIVE_FRAME_INFO2:
            pDrives[ucDriveIndex].ucMotorTemp = UnScaleTemp(pMessage->data[0]);
            pDrives[ucDriveIndex].ucControllerTemp = UnScaleTemp(pMessage->data[1]);
            pDrives[ucDriveIndex].usDPotentiometer = (pMessage->data[2] << 8) & 0xFF00;
            pDrives[ucDriveIndex].usDPotentiometer |= pMessage->data[3];
            pDrives[ucDriveIndex].usAnalogIn = (pMessage->data[4] << 8) & 0xFF00;
            pDrives[ucDriveIndex].usAnalogIn |= pMessage->data[5];
            pDrives[ucDriveIndex].unBatteryCurrent = UnScalePeakCurrent(((pMessage->data[6] << 8) & 0xFF00)| pMessage->data[7]);
            break;
    }
}

void ReturnDriveInformation(DRIVE_STATUS *pDrives, unsigned char ucDriveIndex, unsigned int *unMotorSpeed, unsigned int *unMotorCurrent, unsigned int *unMotorTemp, unsigned int *unControllerTemp, unsigned int *unBatteryCurrent, unsigned int *unBatteryVoltage, unsigned int *unDriveStatus)
{
    if(NBROFDRIVE <= ucDriveIndex)
        return;

    //Motor Speed
    unMotorSpeed[0] = abs(pDrives[ucDriveIndex].nMotorSpeed);
    //Motor Current (RMS)
    unMotorCurrent[0] = pDrives[ucDriveIndex].unMotorCurrent;
    //Motor Temperature
    unMotorTemp[0] = pDrives[ucDriveIndex].ucMotorTemp;
    //Controller Temperature
    unControllerTemp[0] = pDrives[ucDriveIndex].ucControllerTemp;
    //Battery Current
    unBatteryCurrent[0] = pDrives[ucDriveIndex].unBatteryCurrent;
    //Battery Voltage
    unBatteryVoltage[0] = pDrives[ucDriveIndex].unBatteryVoltage;
    //Drive status
    unDriveStatus[0] = pDrives[ucDriveIndex].ucStatus;
}

unsigned short ScaleTorque(float fValue)
{
    return (unsigned short)(fValue*TORQUE_SCALING_K+TORQUE_SCALING_B);
}

unsigned short ScaleSpeed(float fValue)
{
    return (unsigned short)(fValue*SPEED_SCALING_K+SPEED_SCALING_B);
}

unsigned short ScaleTemp(unsigned short usValue)
{
    return  TEMP_CONVERTING_OFFSET+usValue;
}

unsigned int UnScaleTemp(unsigned char ucValue)
{
    return (unsigned int)(ucValue-TEMP_CONVERTING_OFFSET);
}

int UnScaleSpeed(unsigned short usValue)
{
    return (int)((((float)usValue-SPEED_SCALING_B)/SPEED_SCALING_K));
}

unsigned int UnScaleVoltage(unsigned short usValue)
{
    return (unsigned int)((((float)usValue-VOLTAGE_SCALING_B)/VOLTAGE_SCALING_K)*DATA_RESOLUTION);
}

unsigned int UnScaleRMSCurrent(unsigned short usValue)
{
    return(unsigned int)((((float)usValue-CURRENT_SCALING_B)/RMS_CURRENT_SCALING_K)*DATA_RESOLUTION);
}

unsigned int UnScalePeakCurrent(unsigned short usValue)
{
    return(unsigned int)((((float)usValue-CURRENT_SCALING_B)/PEAK_CURRENT_SCALING_K)*DATA_RESOLUTION);
}


void PoolingDrive(DRIVE_STATUS *pDrives, unsigned char ucDriveIndex, unsigned char usCommandType)
{
    DRIVE_MSG driveMessage;

    driveMessage.RTR = 1;
    driveMessage.address = pDrives[ucDriveIndex].unBaseAddrWrite;
    driveMessage.dataLenght = 8;
    driveMessage.ucType = usCommandType;
    
    CanNETSACTxMessage(&driveMessage, D_CAN2);
}

void PoolingDrives(DRIVE_STATUS *pDrives)
{
    unsigned char i = 0;
    for(i = 0 ; i<NBROFDRIVE; i++)
    {
        PoolingDrive(pDrives, i, DRIVE_FRAME_INFO1);
        PoolingDrive(pDrives, i, DRIVE_FRAME_INFO2);
    }
}