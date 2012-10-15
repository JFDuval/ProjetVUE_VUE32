

#include "VUE32_Impl.h"


// Prototypes
void InitVUE32_0(void);
void InitVUE32_1(void);
void InitVUE32_2(void);
void InitVUE32_3(void);
void InitVUE32_4(void);
void InitVUE32_5(void);
void InitVUE32_6(void);
void InitVUE32_7(void);
void ImplVUE32_0(void);
void ImplVUE32_1(void);
void ImplVUE32_2(void);
void ImplVUE32_3(void);
void ImplVUE32_4(void);
void ImplVUE32_5(void);
void ImplVUE32_6(void);
void ImplVUE32_7(void);
void OnMsgVUE32_0(NETV_MESSAGE *msg);
void OnMsgVUE32_1(NETV_MESSAGE *msg);
void OnMsgVUE32_2(NETV_MESSAGE *msg);
void OnMsgVUE32_3(NETV_MESSAGE *msg);
void OnMsgVUE32_4(NETV_MESSAGE *msg);
void OnMsgVUE32_5(NETV_MESSAGE *msg);
void OnMsgVUE32_6(NETV_MESSAGE *msg);
void OnMsgVUE32_7(NETV_MESSAGE *msg);
extern HDW_MAPPING gVUE32_0_Ress[];
extern HDW_MAPPING gVUE32_1_Ress[];
extern HDW_MAPPING gVUE32_2_Ress[];
extern HDW_MAPPING gVUE32_3_Ress[];
extern HDW_MAPPING gVUE32_4_Ress[];
extern HDW_MAPPING gVUE32_5_Ress[];
extern HDW_MAPPING gVUE32_6_Ress[];
extern HDW_MAPPING gVUE32_7_Ress[];

extern ROUTING_TABLE gRoutingTableVUE32_0[];
extern ROUTING_TABLE gRoutingTableVUE32_1[];
extern ROUTING_TABLE gRoutingTableVUE32_2[];
extern ROUTING_TABLE gRoutingTableVUE32_3[];
extern ROUTING_TABLE gRoutingTableVUE32_4[];
extern ROUTING_TABLE gRoutingTableVUE32_5[];
extern ROUTING_TABLE gRoutingTableVUE32_6[];
extern ROUTING_TABLE gRoutingTableVUE32_7[];

void OnEmergencyMsgVUE32_0();
void OnEmergencyMsgVUE32_1();
void OnEmergencyMsgVUE32_2();
void OnEmergencyMsgVUE32_3();
void OnEmergencyMsgVUE32_4();
void OnEmergencyMsgVUE32_5();
void OnEmergencyMsgVUE32_6();
void OnEmergencyMsgVUE32_7();


// Arrays of function pointers for each implementation
FUNC_INIT gInitFunc[NB_VUE32+1] = {
    ImplVUE32_0,
    InitVUE32_1,
    InitVUE32_2,
    InitVUE32_3,
    InitVUE32_4,
    InitVUE32_5,
    InitVUE32_6,
    InitVUE32_7,
};

FUNC_IMPL gImplFunc[NB_VUE32+1] = {
    ImplVUE32_0,
    ImplVUE32_1,
    ImplVUE32_2,
    ImplVUE32_3,
    ImplVUE32_4,
    ImplVUE32_5,
    ImplVUE32_6,
    ImplVUE32_7,
};

FUNC_ONMSG gOnMsgFunc[NB_VUE32+1] = {
    OnMsgVUE32_0,
    OnMsgVUE32_1,
    OnMsgVUE32_2,
    OnMsgVUE32_3,
    OnMsgVUE32_4,
    OnMsgVUE32_5,
    OnMsgVUE32_6,
    OnMsgVUE32_7,
};


HDW_MAPPING* gHardwareMap[NB_VUE32+1] = {
    gVUE32_0_Ress,
    gVUE32_1_Ress,
    gVUE32_2_Ress,
    gVUE32_3_Ress,
    gVUE32_4_Ress,
    gVUE32_5_Ress,
    gVUE32_6_Ress,
    gVUE32_7_Ress
};

unsigned int gHardwareSize[NB_VUE32+1] =
{
    0,  //VUE32_0
    0,  //VUE32_1
    3,  //VUE32_2
    2,  //VUE32_3
    2,  //VUE32_4
    7,  //VUE32_5
    3,  //VUE32_6
    1   //VUE32_7
};

FUNC_ONEMERGMSG gOnEmergencyMsgVUE32[NB_VUE32+1] =
{
    OnEmergencyMsgVUE32_0,
    OnEmergencyMsgVUE32_1,
    OnEmergencyMsgVUE32_2,
    OnEmergencyMsgVUE32_3,
    OnEmergencyMsgVUE32_4,
    OnEmergencyMsgVUE32_5,
    OnEmergencyMsgVUE32_6,
    OnEmergencyMsgVUE32_7
};

ROUTING_TABLE *gRoutingTable[NB_VUE32+1] =
{
    gRoutingTableVUE32_0,
    gRoutingTableVUE32_1,
    gRoutingTableVUE32_2,
    gRoutingTableVUE32_3,
    gRoutingTableVUE32_4,
    gRoutingTableVUE32_5,
    gRoutingTableVUE32_6,
    gRoutingTableVUE32_7
};

unsigned char gRoutingTableSize[NB_VUE32+1] =
{
    0,  //VUE32_0
    0,  //VUE32_1
    0,  //VUE32_2
    0,  //VUE32_3
    0,  //VUE32_4
    0,  //VUE32_5
    NB_BMS,  //VUE32_6
};

