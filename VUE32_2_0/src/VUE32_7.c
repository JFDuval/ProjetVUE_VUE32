/******************************************************************************
 * VUE32 #7 functions implementation
 *  - CAN2: BMS
 *  - Speed sensor, Rear Left
 *  - Lights: Rear Left
 *
 * by Maxime Bedard - 24/09/2012
 * ****************************************************************************/

#include "NETV32_Common.h"
#include "HardwareProfile.h"
#include "VUE32_Utils.h"
#include "VUE32_Impl.h"

#include "def.h"
#include "Board.h"

//Hardware resources manage localy by this VUE32
HDW_MAPPING gVUE32_7_Ress[] =
{
    {E_ID_WHEELVELOCITYSSENSOR_BL, 4, 0x00}
};

/*
 * Specific Initialization
 */
void InitVUE32_7(void)
{

}

/*
 * State Machine Processing
 */
void ImplVUE32_7(void)
{

}

/*
 * Message Processing
 */
void OnMsgVUE32_7(NETV_MESSAGE *msg)
{
    ON_MSG_TYPE_RTR(VUE32_TYPE_GETVALUE)
                ANSWER1(E_ID_WHEELVELOCITYSSENSOR_BL, unsigned int, 7)
                LED2 = ~LED2;
    END_OF_MSG_TYPE
}

//TODO Put emergency instructions here
void OnEmergencyMsgVUE32_7(void)
{
    return;
}

ROUTING_TABLE gRoutingTableVUE32_7[24] =
{
    {NETV_COMM_IFACE_CAN2, BMS_1},
    {NETV_COMM_IFACE_CAN2, BMS_2},
    {NETV_COMM_IFACE_CAN2, BMS_3},
    {NETV_COMM_IFACE_CAN2, BMS_4},
    {NETV_COMM_IFACE_CAN2, BMS_5},
    {NETV_COMM_IFACE_CAN2, BMS_6},
    {NETV_COMM_IFACE_CAN2, BMS_7},
    {NETV_COMM_IFACE_CAN2, BMS_8},
    {NETV_COMM_IFACE_CAN2, BMS_9},
    {NETV_COMM_IFACE_CAN2, BMS_10},
    {NETV_COMM_IFACE_CAN2, BMS_11},
    {NETV_COMM_IFACE_CAN2, BMS_12},
    {NETV_COMM_IFACE_CAN2, BMS_13},
    {NETV_COMM_IFACE_CAN2, BMS_14},
    {NETV_COMM_IFACE_CAN2, BMS_15},
    {NETV_COMM_IFACE_CAN2, BMS_16},
    {NETV_COMM_IFACE_CAN2, BMS_17},
    {NETV_COMM_IFACE_CAN2, BMS_18},
    {NETV_COMM_IFACE_CAN2, BMS_19},
    {NETV_COMM_IFACE_CAN2, BMS_20},
    {NETV_COMM_IFACE_CAN2, BMS_21},
    {NETV_COMM_IFACE_CAN2, BMS_22},
    {NETV_COMM_IFACE_CAN2, BMS_23},
    {NETV_COMM_IFACE_CAN2, BMS_24}
};