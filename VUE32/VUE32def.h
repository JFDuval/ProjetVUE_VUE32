
#ifndef VUE32DEF_H
#define VUE32DEF_H


// ******** CARTE VUE32 #1 **********


// ******** CARTE VUE32 #2 ********** 
#define PWR_PIN_POSITION_COOLING_PUMP 1


// ******** CARTE VUE32 #3 et #4 **********
#define VUE32_3_4_PWM_MOTOR (MOTOR_SLOT_A | MOTOR_SLOT_B)  //motor for the window
//mA
#define VUE32_3_4_MOTOR_A_MAX_CURRENT 1000  
#define VUE32_3_4_MOTOR_B_MAX_CURRENT 1000  
#define MOTOR_LOCK MOTOR_A
#define MOTOR_WINDOW MOTOR_B

// ******** CARTE VUE32 #5a *********
#define VUE32_5A_PWM_MOTOR (MOTOR_SLOT_A | MOTOR_SLOT_B)
//mA
#define VUE32_5A_MOTOR_A_MAX_CURRENT 1000
#define VUE32_5A_MOTOR_B_MAX_CURRENT 1000
#define PWR_PIN_POSITION_LEFT_LIGHT 1
#define PWR_PIN_POSITION_RIGHT_LIGHT 2
#define PWR_PIN_POSITION_LOW_LIGHT 3
#define PWR_PIN_POSITION_WIPER_FRONT_PUMP 4


// ******** CARTE VUE32 #5b *********
#define PWR_PIN_POSITION_HIGH_LIGHT 1
#define PWR_PIN_POSITION_BRAKE_LIGHT 2
#define PWR_PIN_POSITION_NIGHT_LIGHT 3


// ******** CARTE VUE32 #6 **********
//#define AD_position_for_PRD_CMD 0   //need detail about this one
#define AD_position_for_ACC_FOOT 1
#define AD_position_for_BRK_FOOT 2
#define STARTER_KEYS                //need detail about this one
#define STEERING_WHEELS_RETRANSMIT  //need detail about this one

// ******** CARTE VUE32 #7 **********
#define SPEED_SENSOR_LEFT_FRONT_PORT 0
#define SPEED_SENSOR_RIGHT_FRONT_PORT 1


// ******** CARTE VUE32 #8 **********
#define SPEED_SENSOR_LEFT_REAR_PORT 0
#define PWR_PIN_POSITION_WIPER_BACK_PUMP 4

// ******** CARTE VUE32 #9 **********


// ******** CARTE VUE32 #10 **********
#define SPEED_SENSOR_RIGHT_REAR_PORT 0

#endif