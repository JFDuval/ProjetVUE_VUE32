/* 
 * File:   VUE32_Impl.h
 * Author: bedm2308
 *
 * Created on 24 septembre 2012, 14:34
 */

#ifndef VUE32_IMPL_H
#define	VUE32_IMPL_H

#include "NETV32_Common.h"
#include "VUE32_Utils.h"

// Number of existing VUE32
#define NB_VUE32 7
#define NB_BMS 24

#define Sensor 1
#define Actuator 0

// Typedefs for the ID-specific function pointers
typedef void (*FUNC_INIT)();
typedef void (*FUNC_IMPL)();
typedef void (*FUNC_ONMSG)(NETV_MESSAGE*);
typedef void (*FUNC_ONEMERGMSG)();
typedef void (*FUNC_CAN2RXDriver)();

// Arrays of function pointers for each implementation
extern FUNC_INIT gInitFunc[NB_VUE32+1];
extern FUNC_IMPL gImplFunc[NB_VUE32+1];
extern FUNC_ONMSG gOnMsgFunc[NB_VUE32+1];
extern FUNC_ONEMERGMSG gOnEmergencyMsgVUE32[NB_VUE32+1];
extern FUNC_CAN2RXDriver gCAN2RXDriver[NB_VUE32+1];


extern HDW_MAPPING *gHardwareMap[NB_VUE32+1];
extern unsigned int gHardwareSize[NB_VUE32+1];

extern ROUTING_TABLE *gRoutingTable[NB_VUE32+1];
extern unsigned char gRoutingTableSize[NB_VUE32+1];
void ReinitFlagsArray();



#endif	/* VUE32_IMPL_H */

