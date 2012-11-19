/* 
 * File:   BatteryPack.h
 * Author: bedm2308
 *
 * Created on 13 novembre 2012, 11:18
 */

#ifndef BATTERYPACK_H
#define	BATTERYPACK_H

#include "../src/NETV32_Common.h"

// Enum for the possible states of the battery pack
typedef enum {InitBQ,InitSleep,Sleep,Balance,Monitor,InitPeripheral,Test,WakeUp,WaitStabiliseTension,WaitStabiliseTemp,ProblemDetected,noComm,Connecting} E_BMS_STATES;

// Initialize state machine for the battery pack
void InitBatteryPack();

// Run the battery pack state machine
void RunBatteryPack();

// Interpretation of BMS messages
void OnBatteryMsg(NETV_MESSAGE *msg);

// Change the state of the whole battery pack
void SetState(E_BMS_STATES eState);

// Get number of currently connected BMS
unsigned short GetNumConnectedBMS();

// Get bms global state
E_BMS_STATES GetBmsGlobalState();

// Get minimum and maximum (higher 16bits) cell tension
unsigned int GetBmsMinMaxTension();

#endif	/* BATTERYPACK_H */

