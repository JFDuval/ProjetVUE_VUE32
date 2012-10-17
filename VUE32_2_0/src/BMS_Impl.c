
// Todo: Make this file cleaner, use VUE32_Impl.c as template

#include "NETV32_Common.h"
#include "VUE32_Utils.h"
#include "BMS_Impl.h"


// Prototypes
void InitBMS(void);

void ImplBMS(void);

void OnMsgBMS(NETV_MESSAGE *msg);

extern HDW_MAPPING gBMS_Ress[];

extern ROUTING_TABLE gRoutingTableBMS_0[];

void OnEmergencyMsgBMS();


// Arrays of function pointers for each implementation
FUNC_INIT gInitFuncBMS[INDEX_BMS] =
{
    InitBMS,
};

FUNC_IMPL gImplFuncBMS[INDEX_BMS] =
{
    ImplBMS,
};

FUNC_ONMSG gOnMsgFuncBMS[INDEX_BMS] =
{
    OnMsgBMS,
};


HDW_MAPPING* gHardwareMapBMS[INDEX_BMS] =
{
    gBMS_Ress,
};

unsigned int gHardwareSizeBMS[INDEX_BMS] =
{
    3   //BMS
};

FUNC_ONEMERGMSG gOnEmergencyMsgBMS[INDEX_BMS] =
{
    OnEmergencyMsgBMS,
};

ROUTING_TABLE *gRoutingTableBMS[INDEX_BMS] =
{
    gRoutingTableBMS_0,
};

unsigned char gRoutingTableSizeBMS[INDEX_BMS] =
{
    0  //BMS
};



