#include "drive.h"


void InitDrive()
{
    //Field drive status

    //Send initialisation Command
}


void DriveTXCmd(unsigned int unBaseId, unsigned short usCommand, unsigned char ucModeSelector, unsigned char ucPowerLimit, unsigned short usTemperatureAD)
{
    MSG_DRIVE driveMessage;
    driveMessage.address = unBaseId;
    driveMessage.ucType = DRIVE_FRAME_CONTROL;

    driveMessage.data[0] = (unsigned char)((usCommand >> 8) & 0x00FF);
    driveMessage.data[1] = (unsigned char)(usCommand & 0x00FF);

    //Motor Selector
    driveMessage.data[2] = ucModeSelector;

    //Power Limit
    driveMessage.data[4] = ucPowerLimit;

    //Temperature
    driveMessage.data[5] = (unsigned char)((usTemperatureAD >> 8) & 0x00FF);
    driveMessage.data[6] = (unsigned char)(usTemperatureAD & 0x00FF);
}

void DriveRXCmd(MSG_DRIVE *pMessage, DRIVE_STATUS * pDrive)
{
    unsigned char i = 0;
    unsigned char ucDriveIndex = 0;

    //Validate if there is a valid BaseID
    for(i = 0; i<NBROFDRIVE; i++)
    {
        if(pDrive[i].unBaseAddr == pMessage->address)
        {
            ucDriveIndex = i;
        }
    }

    //Returning if no drive has been found
    if(!ucDriveIndex)
        return;

    //payload parser
    switch(pMessage->ucType)
    {
        case DRIVE_FRAME_INFO1:
            pDrive[i].usMotorSpeed = (pMessage->data[0] << 8) & 0xFF00;
            pDrive[i].usMotorSpeed |= (pMessage->data[1]);
            pDrive[i].usBatteryVoltage  = (pMessage->data[2] << 8) & 0xFF00;
            pDrive[i].usBatteryVoltage |= (pMessage->data[3]);
            pDrive[i].usMotorCurrent = (pMessage->data[4] << 8) & 0xFF00;
            pDrive[i].usMotorCurrent |= (pMessage->data[5]);
            pDrive[i].usStatus = (pMessage->data[6] << 8) & 0xFF00;
            pDrive[i].usStatus |=  (pMessage->data[7]);
            break;
        case DRIVE_FRAME_INFO2:
            pDrive[i].ucMotorTemp = (pMessage->data[0] << 8) & 0xFF00;
            pDrive[i].ucMotorTemp |= pMessage->data[1];
            pDrive[i].usDPotentiometer = (pMessage->data[2] << 8) & 0xFF00;
            pDrive[i].usDPotentiometer |= pMessage->data[3];
            pDrive[i].usAnalogIn = (pMessage->data[4] << 8) & 0xFF00;
            pDrive[i].usAnalogIn |= pMessage->data[5];
            pDrive[i].usBatteryCurrent = (pMessage->data[6] << 8) & 0xFF00;
            pDrive[i].usBatteryCurrent |= pMessage->data[7];
            break;
    }
}

unsigned short ScaleTorqueValue(float fValue)
{
        float m = (CAN_TORQUE_SCALING_B-CAN_TORQUE_SCALING_A)/65534;
}