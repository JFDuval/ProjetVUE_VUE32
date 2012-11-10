#ifndef DRIVE_H
#define DRIVE_H

#define NBROFDRIVE 2

#define DRIVE_RIGHT      16              //Passenger side
#define DRIVE_LEFT       32              //Driver side

#define DRIVE_FRAME_ENABLE_DISABLE 0
#define DRIVE_FRAME_CONTROL 1
#define DRIVE_FRAME_INFO1 2
#define DRIVE_FRAME_INFO2 3
#define CAN_TORQUE_SCALING_A    10      //To define
#define CAN_TORQUE_SCALING_B    62000   //To define

//Mode selector
#define SPEED_MODE 0
#define TORQUE_MODE 1
#define EV_MODE 2

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
    unsigned char data[8];

}MSG_DRIVE;

typedef struct
{
    unsigned int unBaseAddr;
    unsigned short usMotorSpeed;
    unsigned short usBatteryVoltage;
    unsigned short usBatteryCurrent;
    unsigned short usMotorCurrent;
    unsigned short usStatus;
    unsigned char ucMotorTemp;
    unsigned char ucControllerTemp;
    unsigned short usDPotentiometer;
    unsigned short usAnalogIn;
}DRIVE_STATUS;

void DriveSendTorque();
void DriveDisable(unsigned char);


#endif