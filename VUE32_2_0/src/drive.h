/******************************************************************************
 * drive driver
 * by Pascal-Frédéric St-Laurent - 08/11/2012
 * ****************************************************************************/

#ifndef DRIVE_H
#define DRIVE_H

#define NBROFDRIVE 2

//CAN interface
#define D_CAN1 0
#define D_CAN2 1

//motor direction
#define NotInverted 0
#define Inverted 1

//Frame id
#define DRIVE_FRAME_ENABLE_DISABLE 0
#define DRIVE_FRAME_CONTROL 1
#define DRIVE_FRAME_INFO1 0
#define DRIVE_FRAME_INFO2 1

//Drive CONTROL STATUS
#define DRIVE_ENABLE 1
#define DRIVE_DISABLE 0

//Drive Emergency Status
#define NO_EMERGENCY 0
#define EMERGENCY 1

//Mode selector
#define SPEED_MODE 0
#define TORQUE_MODE 1
#define EV_MODE 2

//Base Id
#define BASE_ID_DRIVE_RIGHT_READ 32             //Passenger side
#define BASE_ID_DRIVE_RIGHT_WRITE 64            //Passenger side
#define BASE_ID_DRIVE_LEFT_READ 128             //Driver side
#define BASE_ID_DRIVE_LEFT_WRITE 256             //Driver side

//Power limitation
#define PL_NO_LIMIT 0
#define PL_MAXIMUM_MOTOR_POWER_LIMIT 127
#define PL_NO_GENERATOR 128
#define PL_MAXIMUM_GENERATOR_LIMIT 255

//Scaler parameters
#define SP_MIN_POTENTIOMETER_POS 0
#define SP_MAX_POTENTIOMETER_POS 1023
#define SP_NEUTRAL_POTENTIOMETER_POS 512
#define SP_POTENTIOMETER_DEAD_ZONE 1
#define SP_POTENTIOMETER_MODE 2

#define TORQUE_SCALING_K    32.7761      //Nm
#define TORQUE_SCALING_B    32767

#define SPEED_SCALING_K 3.27701         //RPM
#define SPEED_SCALING_B 32767

#define VOLTAGE_SCALING_K 100           //Volt peak
#define VOLTAGE_SCALING_B 0

#define PEAK_CURRENT_SCALING_K 77.234987    //Amp
#define RMS_CURRENT_SCALING_K 24.61496      //Amp
#define CURRENT_SCALING_B 32767

#define TEMP_CONVERTING_OFFSET 55

//Data Resolution read by ODB
#define DATA_RESOLUTION 1000

//Error Code
#define NO_ERROR 0
#define OVER_CURRENT 1
#define OVER_VOLTAGE 2
#define UNDER_VOLTAGE 3
#define BATTERY_VOLTAGE_LOW_AT_START 4
#define POTENTIOMETER_ERROR_DURING_OPERATION 5
#define POTENTIOMETER_NOT_ZERO_AT_START 6
#define OVER_TEMPERATURE 7
#define UNDER_TEMPERATURE 8
#define TEMPERATURE_SENSOR_ERROR 9
#define CURRENT_OFFSET_ERROR 10
#define DC_LINK_CHARGING_ERROR 11
#define RELAY_ERROR 12
#define PDINTA 13
#define BAD_USER_PARAMETE_CRC 14
#define BAD_SYSTEM_PARAMETER_CRC 15
#define BAD_FLASH_CRC 16
#define WRONG_PARAMETER_VERSION 17
#define INVALID_MOTOR_TYPE 18
#define AUTOTUNING_ERROR 19
#define BOOST_ERROR 20
#define MOTOR_OVER_TEMPERATURE 21
#define MOTOR_TEMPERATURE_SENSOR_ERROR 22
#define STALL_DETECTED 23
#define MOTOR_OVERSPEED 24

typedef struct
{
    unsigned int address;
    unsigned char ucType;
    unsigned char dataLenght;
    unsigned char data[8];
    unsigned char RTR;

}DRIVE_MSG;

typedef struct
{
    unsigned char ucIsEnable;
    unsigned int unBaseAddrRead;
    unsigned int unBaseAddrWrite;
    int nMotorSpeed;
    unsigned int unBatteryVoltage;
    unsigned int unBatteryCurrent;
    unsigned int unMotorCurrent;
    unsigned char ucStatus;
    unsigned char ucMotorTemp;
    unsigned char ucControllerTemp;
    unsigned short usDPotentiometer;
    unsigned short usAnalogIn;
    unsigned short usMotorCommand;          //The nature of this command depends on the drive mode which coulb be Speed, torque or EV mode
    float ufMotorCommand;
    unsigned char ucSelectedMode;
    unsigned char ucPowerLimit;
    unsigned short usMotorTempADC;
    unsigned char ucIsOnEmergency;
    unsigned char ucIsInvert;
}DRIVE_STATUS;


//Index used for the drive status struct array
enum driveIndex
{
    RightDrive,
    LeftDrive,
};


void DriveEnable(DRIVE_STATUS *pDrives, unsigned char ucDriveIndex);
void DriveDisable(DRIVE_STATUS *pDrives, unsigned char ucDriveIndex);
void DriveStateMachine(DRIVE_STATUS *pDrives, unsigned char ucDriveIndex, float fCommandMotor, short usUnscaledTemp);
char DrivesError(DRIVE_STATUS *pDrives);
void DriveTXCmd(DRIVE_STATUS *pDrive);
void DriveRXCmd(DRIVE_MSG *pMessage, DRIVE_STATUS *pDrives);
void ReturnDriveInformation(DRIVE_STATUS *pDrives, unsigned char ucDriveIndex, unsigned int *unMotorSpeed, unsigned int *unMotorCurrent, unsigned int *unMotorTemp, unsigned int *unControllerTemp, unsigned int *unBatteryCurrent, unsigned int *unBatteryVoltage, unsigned int *unDriveStatus);

unsigned short ScaleTorque(float fValue);
unsigned short ScaleSpeed(float fValue);
unsigned short ScaleTemp(unsigned short usValue);
unsigned int UnScaleTemp(unsigned char ucValue);
unsigned int UnScalePeakCurrent(unsigned short usValue);
unsigned int UnScaleRMSCurrent(unsigned short usValue);
unsigned int UnScaleVoltage(unsigned short usValue);
int UnScaleSpeed(unsigned short usValue);


void PoolingDrive(DRIVE_STATUS *pDrives, unsigned char ucDriveIndex, unsigned char usCommandType);
void PoolingDrives(DRIVE_STATUS *pDrives);


#endif