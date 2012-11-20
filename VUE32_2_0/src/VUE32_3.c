/******************************************************************************
 * VUE32 #3 functions implementation
 *  - CAN2: Drives
 *  - Speed sensor, front right
 *  - Speed sensor, front left
 *  - Main contactor
 *  - Cooling pump
 *
 * by Maxime Bedard - 24/09/2012
 * ****************************************************************************/

#include "NETV32_Common.h"
#include "HardwareProfile.h"
#include "VUE32_Utils.h"
#include "VUE32_Impl.h"
#include "def.h"

//Interface between hardware and communication
//memory_map.h
extern unsigned int gResourceMemory[256];

//wheel_sensor.c
extern unsigned short spdo1_mean, spdo2_mean;
extern volatile unsigned char spd1_moving, spd2_moving;
unsigned short wheel_spdo1_kph_VUE32_3 = 0, wheel_spdo2_kph_VUE32_3 = 0;

extern volatile unsigned int flag_1ms_b;
extern volatile unsigned char flag_drives;
extern volatile unsigned int flag_8ms;

extern volatile unsigned int uiTimeStamp;

unsigned int usStartedTime;
unsigned char ucReady = 0;
unsigned char drives = 1;

//Hardware resources manage localy by this VUE32
HDW_MAPPING gVUE32_3_Ress[] =
{
    {E_ID_WHEELVELOCITYSSENSOR_FR, 4, Sensor},
    {E_ID_WHEELVELOCITYSSENSOR_FL, 4, Sensor},
    {E_ID_BRAKEPEDAL, sizeof(unsigned short), Sensor},      //TO REMOVE
    {E_ID_ACCELERATOR, sizeof(unsigned short), Sensor},     //TO REMOVE
    {E_ID_DPR, sizeof(unsigned char), Sensor},              //TO REMOVE
    {E_ID_COOLINGPUMP, 1, Actuator},
    {E_ID_MAIN_CONTACTOR, 1, Actuator}
};

DRIVE_STATUS gDrivesVUE32_3[NBROFDRIVE] =
{
    {DRIVE_DISABLE, BASE_ID_DRIVE_RIGHT_READ, BASE_ID_DRIVE_RIGHT_WRITE, 0, 0, NO_ERROR, 0,0,0,0,0,0, TORQUE_MODE, PL_NO_LIMIT, 0, 0, NO_EMERGENCY},
    {DRIVE_DISABLE, BASE_ID_DRIVE_LEFT_READ, BASE_ID_DRIVE_LEFT_WRITE, 0, 0, NO_ERROR, 0,0,0,0,0,0, TORQUE_MODE, PL_NO_LIMIT, 0, 0, NO_EMERGENCY},
};

// Mapping between pins and functionnalities,
#define WHEELVELOCITYSSENSOR_FR SPDO1
#define WHEELVELOCITYSSENSOR_FL SPDO2
#define WHEELVELOCITYSSENSOR_FL_TRIS SPDO2_TRIS

unsigned int tm_unRandom = 65000;

/*
 * Specific Initialization
 */
void InitVUE32_3(void)
{
    power_out(MISC_PWR_COOLING,1);
    power_out(MISC_PWR_CONTACTOR,1);
    gDrivesVUE32_3[0].ucSelectedMode = TORQUE_MODE;
    gDrivesVUE32_3[1].ucSelectedMode = TORQUE_MODE;

    usStartedTime = uiTimeStamp+5000;
    // Set the LED2 as output (test)
    LED2_TRIS = 0;

    gResourceMemory[E_ID_DPR] = 0x01;
    gResourceMemory[E_ID_MOTOR_TEMP2] = 0x8034;
}

/*
 * State Machine Processing
 */
void ImplVUE32_3(void)
{
    if(flag_1ms_b)
    {
        flag_1ms_b = 0;

        asm volatile ("di"); //Disable int
        filter_wheel();
        asm volatile ("ei"); //Enable int
	wheel_spdo1_kph_VUE32_3 = wheel_period_to_kph(spdo1_mean, spd1_moving);
	wheel_spdo2_kph_VUE32_3 = wheel_period_to_kph(spdo2_mean, spd2_moving);
    }

    if(usStartedTime < uiTimeStamp  && drives)
    {
        drives = 0;
        DriveEnable(gDrivesVUE32_3, LeftDrive);
        DriveEnable(gDrivesVUE32_3, RightDrive);
        
    }

    if(flag_drives)
    { 
        flag_drives = 0;
        
        DriveStateMachine(gDrivesVUE32_3, LeftDrive, (float)gResourceMemory[E_ID_ACCELERATOR]*-0.16, (unsigned short)gResourceMemory[E_ID_MOTOR_TEMP1]);
        DriveStateMachine(gDrivesVUE32_3, RightDrive, (float)gResourceMemory[E_ID_ACCELERATOR]*0.16, (unsigned short)gResourceMemory[E_ID_MOTOR_TEMP2]);
        
        
        /*DRIVE_MSG driveMessage;
        driveMessage.address = 0x20;
        driveMessage.RTR = 0;
        driveMessage.ucType = DRIVE_FRAME_CONTROL;
        driveMessage.dataLenght = 8;
        
        //speed
        unsigned short usSpeed = ScaleSpeedValue((float)gResourceMemory[E_ID_ACCELERATOR]*6);
        //unsigned short usSpeed = ScaleSpeedValue(150);
        driveMessage.data[0] = (unsigned char)((usSpeed >> 8) & 0x00FF);
        driveMessage.data[1] = (unsigned char)(usSpeed & 0x00FF);

        //Motor Selector
        driveMessage.data[2] = SPEED_MODE;

        //Power Limit
        driveMessage.data[3] = PL_NO_LIMIT;

        //Temperature
        unsigned short fTemp = ScaleMotorTempValue(35);
        driveMessage.data[4] = 0;
        driveMessage.data[5] = 85;
        CanNETSACTxMessage(&driveMessage, D_CAN2);*/
    }


}

/*
 * Message Processing for NETV stack only
 */
void OnMsgVUE32_3(NETV_MESSAGE *msg)
{
        // Deal with GETVALUE requests
        ON_MSG_TYPE_RTR(VUE32_TYPE_GETVALUE)
            ANSWER1(E_ID_WHEELVELOCITYSSENSOR_FR, unsigned int, gResourceMemory[E_ID_WHEELVELOCITYSSENSOR_FR])
            ANSWER1(E_ID_WHEELVELOCITYSSENSOR_FL, unsigned int, gResourceMemory[E_ID_WHEELVELOCITYSSENSOR_FL])
            ANSWER1(E_ID_COOLINGPUMP, unsigned char, gResourceMemory[E_ID_COOLINGPUMP])
            ANSWER1(E_ID_MAIN_CONTACTOR, unsigned char, gResourceMemory[E_ID_MAIN_CONTACTOR])
            com_led_toggle();
        END_OF_MSG_TYPE

        ON_MSG_TYPE_RTR(VUE32_TYPE_SETVALUE)
            ANSWER1(E_ID_COOLINGPUMP, unsigned char, gResourceMemory[E_ID_COOLINGPUMP])
            ANSWER1(E_ID_MAIN_CONTACTOR, unsigned char, gResourceMemory[E_ID_MAIN_CONTACTOR])
            com_led_toggle();
        END_OF_MSG_TYPE

        ON_MSG_TYPE( NETV_TYPE_EVENT )
            unsigned char temp;
            /*ACTION1(E_ID_GROUNDFAULT_FREQ, unsigned char, temp)
            END_OF_ACTION*/
            ACTION1(E_ID_DPR, unsigned char, gResourceMemory[E_ID_DPR]) END_OF_ACTION
            ACTION1(E_ID_ACCELERATOR, unsigned short, gResourceMemory[E_ID_ACCELERATOR]) END_OF_ACTION
            ACTION1(E_ID_BRAKEPEDAL, unsigned short, gResourceMemory[E_ID_BRAKEPEDAL]) END_OF_ACTION
            ACTION1(E_ID_MOTOR_TEMP1, unsigned short, gResourceMemory[E_ID_MOTOR_TEMP1]) END_OF_ACTION
            ACTION1(E_ID_MOTOR_TEMP2, unsigned short, gResourceMemory[E_ID_MOTOR_TEMP2]) END_OF_ACTION
            com_led_toggle();
        END_OF_MSG_TYPE
}


//TODO Put emergency instructions here
void OnEmergencyMsgVUE32_3(void)
{
    return;
}


ROUTING_TABLE *gRoutingTableVUE32_3 = NULL;


void gCAN2DriverRX_VUE32_3()
{
    DRIVE_MSG message = {0};
    unsigned int i = 0;

    //Extract the message from CAN2 buffer
    if(CanNETSACRxMessage(&message, 0x01))
    {
        //Proccess the drives network stack          
        DriveRXCmd(&message, gDrivesVUE32_3);

        NETV_MESSAGE messageUSB;
        messageUSB.msg_comm_iface = NETV_COMM_IFACE_USB;
        messageUSB.msg_source = 0;
        messageUSB.msg_priority = 0;
        messageUSB.msg_dest = 0;
        messageUSB.msg_data_length = 8;
        messageUSB.msg_cmd = (unsigned char)message.address;
        messageUSB.msg_type = (unsigned char)message.ucType;
        messageUSB.msg_remote = 0;

        unsigned int i = 0;

        for(i = 0; i<8; i++)
        {
            messageUSB.msg_data[i] = message.data[i];
        }

        usb_netv_send_message(&messageUSB);
    }
}


//TODO
/*void gCAN2DriverTX_VUE32_3(CANRxMessageBuffer*)
{
    return;
}*/

