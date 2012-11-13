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
    {DRIVE_DISABLE, BASE_ID_DRIVE_RIGHT, 0, 0, NO_ERROR, 0,0,0,0,0,0, SPEED_MODE, PL_MAXIMUM_MOTOR_POWER_LIMIT, 0, 0, NO_EMERGENCY},
    {DRIVE_DISABLE, BASE_ID_DRIVE_LEFT, 0, 0, NO_ERROR, 0,0,0,0,0,0, SPEED_MODE, PL_MAXIMUM_MOTOR_POWER_LIMIT, 0, 0, NO_EMERGENCY},
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

    //TODO Manage the driver mode with the DPR switch
    DriveEnable(gDrivesVUE32_3, RightDrive);
   //DriveEnable(gDrivesVUE32_3, LeftDrive);
    
    // Set the LED2 as output (test)
    LED2_TRIS = 0;

    gResourceMemory[E_ID_DPR] = 0x01;
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


    if(flag_drives)
    {
        flag_drives = 0;
        /*PoolingDrive(gDrivesVUE32_3, RightDrive, 0);
        PoolingDrive(gDrivesVUE32_3, RightDrive, 1);
        PoolingDrive(gDrivesVUE32_3, RightDrive, DRIVE_FRAME_INFO1);
        PoolingDrive(gDrivesVUE32_3, RightDrive, DRIVE_FRAME_INFO2);*/
        //DriveStateMachine(gDrivesVUE32_3, RightDrive, 10, 20);
        //DriveStateMachine(gDrivesVUE32_3, LeftDrive, 10, 75);
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
            LED2 = ~LED2;
        END_OF_MSG_TYPE

        ON_MSG_TYPE_RTR(VUE32_TYPE_SETVALUE)
            ANSWER1(E_ID_COOLINGPUMP, unsigned char, gResourceMemory[E_ID_COOLINGPUMP])
            ANSWER1(E_ID_MAIN_CONTACTOR, unsigned char, gResourceMemory[E_ID_MAIN_CONTACTOR])
            LED2 = ~LED2;
        END_OF_MSG_TYPE

        ON_MSG_TYPE( NETV_TYPE_EVENT )
            ACTION1(E_ID_DPR, unsigned char, gResourceMemory[E_ID_DPR]) END_OF_ACTION
            ACTION1(E_ID_ACCELERATOR, unsigned short, gResourceMemory[E_ID_ACCELERATOR]) END_OF_ACTION
            ACTION1(E_ID_BRAKEPEDAL, unsigned short, gResourceMemory[E_ID_BRAKEPEDAL]) END_OF_ACTION
            LED2 = ~LED2;
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

    //Extract the message from CAN2 buffer
    if(CanNETSACRxMessage(&message, 0x01))
        //Proccess the drives network stack
        DriveRXCmd(&message, gDrivesVUE32_3);
}


//TODO
/*void gCAN2DriverTX_VUE32_3(CANRxMessageBuffer*)
{
    return;
}*/
