/* 
 * File:   BMS_Impl.h
 * Author: blackrolla
 *
 * Created on 16 octobre 2012, 14:05
 */

#ifndef BMS_IMPL_H
#define	BMS_IMPL_H

#include "NETV32_Common.h"
#include "VUE32_Utils.h"
#include "VUE32_Impl.h"

// Number of existing BMS
#define INDEX_BMS 1
#define Sensor 1
#define Actuator 0

// Typedefs for the ID-specific function pointers
//typedef void (*FUNC_INIT)();
//typedef void (*FUNC_IMPL)();
//typedef void (*FUNC_ONMSG)(NETV_MESSAGE*);
// void (*FUNC_ONEMERGMSG)();

// Arrays of function pointers for each implementation
extern FUNC_INIT gInitFuncBMS[INDEX_BMS];
extern FUNC_IMPL gImplFuncBMS[INDEX_BMS];
extern FUNC_ONMSG gOnMsgFuncBMS[INDEX_BMS];
extern FUNC_ONEMERGMSG gOnEmergencyMsgBMS[INDEX_BMS];


extern HDW_MAPPING *gHardwareMapBMS[INDEX_BMS];
extern unsigned int gHardwareSizeBMS[INDEX_BMS];

extern ROUTING_TABLE *gRoutingTableBMS[INDEX_BMS];
extern unsigned char gRoutingTableSizeBMS[INDEX_BMS];

#endif	/* BMS_IMPL_H */

