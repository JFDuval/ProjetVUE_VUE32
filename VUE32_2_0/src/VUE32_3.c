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
#include "Board.h"
#include "def.h"
#include "Compensation.h"

// Wheels : Right = Passenger side, Left = Driver side
// Wheels compensation : 1 = Front driver side, 2 = Front passenger side, 3 = Rear driver side, 4 = Rear passenger side
// Motors : 1 = Driver side, 2 = Passenger side

//Interface between hardware and communication
//memory_map.h
extern unsigned int gResourceMemory[256];

//wheel_sensor.c
extern unsigned short spdo1_mean, spdo2_mean;
extern volatile unsigned char spd1_moving, spd2_moving;

extern volatile unsigned int flag_1ms_b;
extern volatile unsigned char flag_drives;
extern volatile unsigned int flag_8ms;
extern volatile unsigned int flag_x100ms;


unsigned int unDPRPreviousState = 0;
float fDirectionMode = 0.0;

// Struct for compensation
motorCommand command;
carMonitor carState;

float uThr;
float slThr;
int gainPp;
int gainPr;
int rollCompThr;
float userCommand;
float gainCorrection;
BOOL otherComp;
float threshold;

typedef union
{
    float val;
    unsigned int raw;
} FloatToInt;

/*Hardware resources manage localy by this VUE32
 * The HDW_MAPPING size has to be set in VUE32_Impl.c
 * gHardwareSize contents size of every gVUE32_X_Ress
 * Note this array is used by long pooling functionnality
 */
HDW_MAPPING gVUE32_3_Ress[] =
{
    {E_ID_WHEELVELOCITYSSENSOR_FR, 4, Sensor},
    {E_ID_WHEELVELOCITYSSENSOR_FL, 4, Sensor},
    {E_ID_LEFT_DRIVE_STATUS, sizeof(unsigned char), Sensor},
    {E_ID_RIGHT_DRIVE_STATUS, sizeof(unsigned char), Sensor},
    {E_ID_LEFT_MOTOR_SPEED, sizeof(unsigned int), Sensor},
    {E_ID_RIGHT_MOTOR_SPEED, sizeof(unsigned int), Sensor},
    {E_ID_LEFT_MOTOR_CURRENT, sizeof(unsigned int), Sensor},
    {E_ID_RIGHT_MOTOR_CURRENT, sizeof(unsigned int), Sensor},
    {E_ID_LEFT_MOTOR_TEMP, sizeof(unsigned char), Sensor},
    {E_ID_RIGHT_MOTOR_TEMP, sizeof(unsigned char), Sensor},
    {E_ID_LEFT_CONTROLLER_TEMP, sizeof(unsigned char), Sensor},
    {E_ID_RIGHT_CONTROLLER_TEMP, sizeof(unsigned char), Sensor},
    {E_ID_LEFT_DRIVE_BATTERY_CURRENT, sizeof(unsigned int), Sensor},
    {E_ID_RIGHT_DRIVE_BATTERY_CURRENT, sizeof(unsigned int), Sensor},
    {E_ID_LEFT_DRIVE_BATTERY_VOLTAGE, sizeof(unsigned int), Sensor},
    {E_ID_RIGHT_DRIVE_BATTERY_VOLTAGE, sizeof(unsigned int), Sensor},
    {E_ID_GLOBAL_CAR_SPEED, sizeof(unsigned short), Sensor},
    {E_ID_COOLINGPUMP, 1, Actuator},
    {E_ID_MAIN_CONTACTOR, 1, Actuator},
    {E_ID_COMP_MOTOR_COMMAND_1, sizeof(unsigned int), Sensor},
    {E_ID_COMP_MOTOR_COMMAND_2, sizeof(unsigned int), Sensor}
};

//Declare drives configuration
//See drive.h
DRIVE_STATUS gDrivesVUE32_3[NBROFDRIVE] = 
{
    {DRIVE_DISABLE, BASE_ID_DRIVE_RIGHT_READ, BASE_ID_DRIVE_RIGHT_WRITE, 0, 0, 0, 0, NO_ERROR, 0,0,0,0,0,0, TORQUE_MODE, PL_NO_LIMIT, 0, NO_EMERGENCY, NotInverted},
    {DRIVE_DISABLE, BASE_ID_DRIVE_LEFT_READ, BASE_ID_DRIVE_LEFT_WRITE, 0, 0, 0, 0, NO_ERROR, 0,0,0,0,0,0, TORQUE_MODE, PL_NO_LIMIT, 0, NO_EMERGENCY, Inverted},
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
	//power_out(3, 1);
	// Set the LED2 as output (test)
    LED2_TRIS = 0;

    // Init speed sensors
    init_change_notification();

    // Initialising compensation values to 0

    carState.ax1 = 0;
    carState.ay1 = 0;
    carState.az1 = 0;
    carState.ax2 = 0;
    carState.ay2 = 0;
    carState.az2 = 0;
    carState.r = 0;
    carState.stWh = 0.0;
    carState.w1 = 0.0;
    carState.w2 = 0.0;
    carState.w3 = 0.0;
    carState.w4 = 0.0;

    //COmpensated motor commands
    command.tmWh3 = 0.0;
    command.tmWh4 = 0.0;

    // Complete compensation parametres
    uThr = 0.05;
    slThr = 0.2;
    gainPp = 150;
    gainPr = 400;
    rollCompThr = 40;
    userCommand = 0.0;
    otherComp = TRUE;

    //Simplified compensation parametres
    gainCorrection = 0.0;
    threshold = 15.0;
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
	gResourceMemory[E_ID_WHEELVELOCITYSSENSOR_FR] = wheel_period_to_kph(spdo1_mean, spd1_moving);
	gResourceMemory[E_ID_WHEELVELOCITYSSENSOR_FL] = wheel_period_to_kph(spdo2_mean, spd2_moving);
    }


    /* Manage motor command sign and drive enabler acconding to DPR switch state*/
    //Car state is on Park, then drives have to be disabled
    if(unDPRPreviousState != gResourceMemory[E_ID_DPR] && gResourceMemory[E_ID_DPR] == PARK)
    {
        unDPRPreviousState = gResourceMemory[E_ID_DPR];
        DriveDisable(gDrivesVUE32_3, LeftDrive);
        DriveDisable(gDrivesVUE32_3, RightDrive);
        fDirectionMode = 0.0;
    }

    //Car state is on Drive or Reverse, then the drives have to be enabled
    if(unDPRPreviousState != gResourceMemory[E_ID_DPR] && (gResourceMemory[E_ID_DPR] == REVERSE || gResourceMemory[E_ID_DPR] == DRIVE))
    {
        unDPRPreviousState = gResourceMemory[E_ID_DPR];
        DriveEnable(gDrivesVUE32_3, LeftDrive);
        DriveEnable(gDrivesVUE32_3, RightDrive);

        //Negative sign
        if(gResourceMemory[E_ID_DPR] == REVERSE)
            fDirectionMode = -1.0;
        //Positive sign
        else if(gResourceMemory[E_ID_DPR] == DRIVE)
            fDirectionMode = 1.0;
    }

    EVERY_X_MS(250)

        //Copy drives informations to the VUE32 application layer
        ReturnDriveInformation(gDrivesVUE32_3, LeftDrive, &gResourceMemory[E_ID_LEFT_MOTOR_SPEED], &gResourceMemory[E_ID_LEFT_MOTOR_CURRENT], &gResourceMemory[E_ID_LEFT_MOTOR_TEMP], &gResourceMemory[E_ID_LEFT_CONTROLLER_TEMP], &gResourceMemory[E_ID_LEFT_DRIVE_BATTERY_CURRENT], &gResourceMemory[E_ID_LEFT_DRIVE_BATTERY_VOLTAGE], &gResourceMemory[E_ID_LEFT_DRIVE_STATUS]);
        ReturnDriveInformation(gDrivesVUE32_3, RightDrive, &gResourceMemory[E_ID_RIGHT_MOTOR_SPEED], &gResourceMemory[E_ID_RIGHT_MOTOR_CURRENT], &gResourceMemory[E_ID_RIGHT_MOTOR_TEMP], &gResourceMemory[E_ID_RIGHT_CONTROLLER_TEMP], &gResourceMemory[E_ID_RIGHT_DRIVE_BATTERY_CURRENT], &gResourceMemory[E_ID_RIGHT_DRIVE_BATTERY_VOLTAGE], &gResourceMemory[E_ID_RIGHT_DRIVE_STATUS]);
        
        //TODO Add the transfert function for to get the exact speed car in Kph
        gResourceMemory[E_ID_GLOBAL_CAR_SPEED] = (gDrivesVUE32_3[RightDrive].nMotorSpeed+gDrivesVUE32_3[LeftDrive].nMotorSpeed)/2;
        SetResourceValue(E_ID_GLOBAL_CAR_SPEED, VUE32_1, sizeof(unsigned short), gResourceMemory[E_ID_GLOBAL_CAR_SPEED]);
    END_OF_EVERY

     // Sending synchronization messages for simplified compensation
     EVERY_X_MS(50)

        NETV_MESSAGE msg = {{0}};

        msg.msg_priority = NETV_PRIORITY_HIGHEST;
        msg.msg_type = NETV_TYPE_SYNCHRONIZE;
        msg.msg_cmd = E_ID_VERSION;
        msg.msg_source = GetMyAddr(); //GetMyAddr();
        msg.msg_dest = 0x05;
        msg.msg_comm_iface = NETV_COMM_IFACE_ALL;
        msg.msg_data_length = 0;
        msg.msg_remote = 1;

        netv_send_message(&msg);

    END_OF_EVERY

    // Calculating compensated torque commands and sending them to the drives
    EVERY_X_MS(50)

            //Getting accelerator pedal command
            userCommand = (float)gResourceMemory[E_ID_ACCELERATOR]*0.31;
            
            //Getting rear wheel speeds (rpm to km/h)
            carState.w3 = (((float)abs(gResourceMemory[E_ID_RIGHT_MOTOR_SPEED])/3.0)*60.0)*(2.0*3.1416*(0.55/2.0))/1000.0;
            carState.w4 = (((float)abs(gResourceMemory[E_ID_LEFT_MOTOR_SPEED])/3.0)*60.0)*(2.0*3.1416*(0.55/2.0))/1000.0;

            //Sending rear wheels speed to the user interface
            FloatToInt conv;
            conv.val = carState.w3;
            gResourceMemory[E_ID_TEST_ALEX_MOTORSPEED1] = conv.raw;
            conv.val = carState.w4;
            gResourceMemory[E_ID_TEST_ALEX_MOTORSPEED2] = conv.raw;

            //Calculating the compensated values
            command = comp(carState, userCommand, gainCorrection, threshold);

            gResourceMemory[E_ID_COMP_MOTOR_COMMAND_1] = command.tmWh3;
            gResourceMemory[E_ID_COMP_MOTOR_COMMAND_2] = command.tmWh4;

            // Sending the calculated commands to the drives
            DriveStateMachine(gDrivesVUE32_3, LeftDrive, command.tmWh3*fDirectionMode, (unsigned short)gResourceMemory[E_ID_LEFT_MOTOR_TEMP_ADC]);
            DriveStateMachine(gDrivesVUE32_3, RightDrive, command.tmWh4*fDirectionMode, (unsigned short)gResourceMemory[E_ID_RIGHT_MOTOR_TEMP_ADC]);

    END_OF_EVERY
}

/*
 * Message Processing for NETV stack only
 */
void OnMsgVUE32_3(NETV_MESSAGE *msg)
{
        // Deal with GETVALUE request

        ON_MSG_TYPE_RTR(VUE32_TYPE_GETVALUE)
            ANSWER1(E_ID_WHEELVELOCITYSSENSOR_FR, unsigned int, gResourceMemory[E_ID_WHEELVELOCITYSSENSOR_FR])
            ANSWER1(E_ID_WHEELVELOCITYSSENSOR_FL, unsigned int, gResourceMemory[E_ID_WHEELVELOCITYSSENSOR_FL])
            ANSWER1(E_ID_LEFT_DRIVE_STATUS, unsigned char, gResourceMemory[E_ID_LEFT_DRIVE_STATUS])
            ANSWER1(E_ID_RIGHT_DRIVE_STATUS, unsigned char, gResourceMemory[E_ID_RIGHT_DRIVE_STATUS])
            ANSWER1(E_ID_LEFT_MOTOR_SPEED, unsigned int, gResourceMemory[E_ID_LEFT_MOTOR_SPEED])
            ANSWER1(E_ID_RIGHT_MOTOR_SPEED, unsigned int, gResourceMemory[E_ID_RIGHT_MOTOR_SPEED])
            ANSWER1(E_ID_LEFT_MOTOR_CURRENT, unsigned int, gResourceMemory[E_ID_LEFT_MOTOR_CURRENT])
            ANSWER1(E_ID_RIGHT_MOTOR_CURRENT, unsigned int, gResourceMemory[E_ID_RIGHT_MOTOR_CURRENT])
            ANSWER1(E_ID_LEFT_MOTOR_TEMP, unsigned char, gResourceMemory[E_ID_LEFT_MOTOR_TEMP])
            ANSWER1(E_ID_RIGHT_MOTOR_TEMP, unsigned char, gResourceMemory[E_ID_RIGHT_MOTOR_TEMP])
            ANSWER1(E_ID_LEFT_CONTROLLER_TEMP, unsigned char, gResourceMemory[E_ID_LEFT_CONTROLLER_TEMP])
            ANSWER1(E_ID_RIGHT_CONTROLLER_TEMP, unsigned char, gResourceMemory[E_ID_RIGHT_CONTROLLER_TEMP])
            ANSWER1(E_ID_RIGHT_CONTROLLER_TEMP, unsigned char, gResourceMemory[E_ID_RIGHT_CONTROLLER_TEMP])
            ANSWER1(E_ID_LEFT_DRIVE_BATTERY_CURRENT, unsigned int, gResourceMemory[E_ID_LEFT_DRIVE_BATTERY_CURRENT])
            ANSWER1(E_ID_RIGHT_DRIVE_BATTERY_CURRENT, unsigned int, gResourceMemory[E_ID_RIGHT_DRIVE_BATTERY_CURRENT])
            ANSWER1(E_ID_LEFT_DRIVE_BATTERY_VOLTAGE, unsigned int, gResourceMemory[E_ID_LEFT_DRIVE_BATTERY_VOLTAGE])
            ANSWER1(E_ID_RIGHT_DRIVE_BATTERY_VOLTAGE, unsigned int, gResourceMemory[E_ID_RIGHT_DRIVE_BATTERY_VOLTAGE])
            ANSWER1(E_ID_COOLINGPUMP, unsigned char, gResourceMemory[E_ID_COOLINGPUMP])
            ANSWER1(E_ID_MAIN_CONTACTOR, unsigned char, gResourceMemory[E_ID_MAIN_CONTACTOR])
            ANSWER1(E_ID_PORT_E, unsigned char, DIO_PORT)
            ANSWER1(E_ID_TRIS_E, unsigned char, DIO_TRIS)
            ANSWER1(E_ID_COMP_MOTOR_COMMAND_1, unsigned int, command.tmWh3)
            ANSWER1(E_ID_COMP_MOTOR_COMMAND_2, unsigned int, command.tmWh4)
            ANSWER1(E_ID_TEST_ALEX_MOTORSPEED1, unsigned int, gResourceMemory[E_ID_TEST_ALEX_MOTORSPEED1])
            ANSWER1(E_ID_TEST_ALEX_MOTORSPEED2, unsigned int, gResourceMemory[E_ID_TEST_ALEX_MOTORSPEED2])
            com_led_toggle();
        END_OF_MSG_TYPE

        ON_MSG_TYPE(VUE32_TYPE_SETVALUE)
            ANSWER1(E_ID_COOLINGPUMP, unsigned char, gResourceMemory[E_ID_COOLINGPUMP])
            ANSWER1(E_ID_MAIN_CONTACTOR, unsigned char, gResourceMemory[E_ID_MAIN_CONTACTOR])
            
            // When receiving new parametres values from the user interface
            FloatToInt conv;

            conv.raw = ((unsigned int*)(msg->msg_data))[0];

            if(msg->msg_cmd == E_ID_COMP_GAIN)
            {
                gainCorrection = conv.val/10;
            }
            if(msg->msg_cmd == E_ID_COMP_UTHR)
            {
                threshold = conv.val;
            }

            com_led_toggle();
        END_OF_MSG_TYPE

        ON_MSG_TYPE( NETV_TYPE_EVENT )
            /*ACTION1(E_ID_GROUNDFAULT_FREQ, unsigned char, temp)
            END_OF_ACTION*/
            ACTION1(E_ID_DPR, unsigned char, gResourceMemory[E_ID_DPR]) END_OF_ACTION
            ACTION1(E_ID_ACCELERATOR, unsigned short, gResourceMemory[E_ID_ACCELERATOR]) END_OF_ACTION
            ACTION1(E_ID_BRAKEPEDAL, unsigned short, gResourceMemory[E_ID_BRAKEPEDAL]) END_OF_ACTION
            ACTION1(E_ID_LEFT_MOTOR_TEMP_ADC, unsigned short, gResourceMemory[E_ID_LEFT_MOTOR_TEMP_ADC]) END_OF_ACTION
            ACTION1(E_ID_RIGHT_MOTOR_TEMP_ADC, unsigned short, gResourceMemory[E_ID_RIGHT_MOTOR_TEMP_ADC]) END_OF_ACTION
            com_led_toggle();
        END_OF_MSG_TYPE

        // On reception of synchronization answer message type
        if(msg->msg_type == NETV_TYPE_SYNCHRONIZE_ANSWER)
        {
            if(msg->msg_cmd == E_ID_STEERINGANGLESENSOR)
            {
                ACTION1(E_ID_STEERINGANGLESENSOR, short, carState.stWh)
                    carState.stWh *= 0.04388772058151229770503794459175;
                END_OF_ACTION
            }
          
        }
}


/* Put emergency instructions here
 * Every device manage by this VUE32 and has to be
 * manage differently in emergency mode
 * must be manage in this function
 */
void OnEmergencyMsgVUE32_3(void)
{
    return;
}

/*
 * Not used
 * Do a static routing between to different network
 * without an network address translation
 */
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
    }
}

//TODO
/*void gCAN2DriverTX_VUE32_3(CANRxMessageBuffer*)
{
    return;
}*/

