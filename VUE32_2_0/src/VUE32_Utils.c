#include "NETV32_Common.h"
#include "def.h"

#include "VUE32_Utils.h"
#include "VUE32_Impl.h"
#
#ifdef __32MX575F512H__
#include "BMS_Impl.h"
#endif

LP_PARAMS g_sLpParams[MAX_NBR_LG_PLG];
unsigned int g_unLpSize = 0;

//Incremented by interrupt each 1 ms
volatile unsigned int uiTimeStamp;


void ActiveLongPolling(LP_PARAMS *sParams)
{
    if ( g_unLpSize == MAX_NBR_LG_PLG || sParams == NULL)
        return;

    //Make sure the ressource id doesn't exist already in the static array
    unsigned int i;
    for(i = 0; i< g_unLpSize; i++)
    {
        if(g_sLpParams[i].ucResourceId == sParams->ucResourceId)
        {
            // This ressource id is already in long polling mode, update its parameters

            //Determine the time when the next sensor value must be sent
            g_sLpParams[i].unDelay = sParams->unDelay;
            
            //Determine when the long polling sensor must died if it never received a renew message
            g_sLpParams[i].unEndPolling = uiTimeStamp+LIFE_TIME_LONG_POLLING;
            return;
        }
    }

    //Determine the time when the next sensor value must be sent
    sParams->unEndWait = uiTimeStamp+sParams->unDelay;
    //Determine when the long polling sensor must died if it never received a renew message
    sParams->unEndPolling = uiTimeStamp+LIFE_TIME_LONG_POLLING;

    g_sLpParams[g_unLpSize++] = *sParams;
}

void DesactivateLongPolling(unsigned char ucRessourceId)
{
    unsigned int i;
    for(i= 0; i<g_unLpSize; i++)
    {
        if(g_sLpParams[i].ucResourceId == ucRessourceId)
        {
            //g_sLpParams[i] = 0;

            //Reorganise the array of ptr
            unsigned int j;
            for(j = i; j < g_unLpSize-1; j++)
            {
                g_sLpParams[j] = g_sLpParams[j+1];
            }

            g_unLpSize--;
        }
    }
}

void RunLongPolling(void)
{
    //For each subcribed sensor to long polling event
    unsigned int i;
    for(i = 0; i<g_unLpSize; i++)
    {
        //Check if it's time to send the sensor's value
        if(g_sLpParams[i].unEndWait <= uiTimeStamp)
        {
            NETV_MESSAGE msg = {0};
            msg.msg_priority = NETV_PRIORITY_EVENTS;
            msg.msg_type = NETV_TYPE_EVENT;
            msg.msg_cmd = g_sLpParams[i].ucResourceId;
            msg.msg_source = GetMyAddr();
            msg.msg_dest = 0x00;
            msg.msg_comm_iface = 0xFF;
            //TODO Link with the application who's interfaced with the hardware layer
            //msg.msg_data_length = g_sLpParams[i]->NbrByte;
            //memcpy(&msg.msg_data, TODO, g_sLpParams[i]->NbrByte);

            //Determine the next time which the board will emit value
            g_sLpParams[i].unEndWait = uiTimeStamp+g_sLpParams[i].unDelay;
            
            netv_send_message(&msg);
            
        }
        
        //Check for the sensor's life time
        if(g_sLpParams[i].unEndPolling <= uiTimeStamp)
        {
            //Desactivating the long polling
            DesactivateLongPolling(g_sLpParams[i].ucResourceId);
        }
    }
}


void ActionStartEmettings(NETV_MESSAGE *msg)
{
    //Is it really a message of type VUE32_TYPE_STARTEMETTING
    if(msg->msg_type != VUE32_TYPE_STARTEMETTING)
        return;

    HDW_MAPPING *gVUE32_Ress;

#ifndef __32MX575F512H__
    gVUE32_Ress = gHardwareMap[GetBoardID()];

    if(gVUE32_Ress == 0)
        return;

    unsigned int unNbResourceId = gHardwareSize[GetBoardID()];
#else

    if(msg->msg_source > NB_VUE32)
    {
        gVUE32_Ress = gHardwareMapBMS[1];
    }

    if(gVUE32_Ress == 0)
        return;

    unsigned int unNbResourceId = gHardwareSizeBMS[1];

#endif


    //Get parameters for long polling
    LP_PARAMS newLongPollingEvent;


    //Verify if this VUE32 has this ressource id
    unsigned int i;
    BOOL bResourceFound= 0;
    for(i = 0;i<unNbResourceId; i++)
    {
        if(gVUE32_Ress[i].ucResourceId == msg->msg_cmd)
            bResourceFound = 1;
    }

    //If this resource isn't available on this VUE32
    if(!bResourceFound)
        return;

    //Load the delay between each transmetting event
    newLongPollingEvent.unDelay = 0;
    memcpy(&newLongPollingEvent.unDelay, msg->msg_data, 2);
    //Safety feature MINIMUM TIME FOR LONG POLLING
    if(newLongPollingEvent.unDelay <= LONG_POLLING_MINIMUM_DELAY)
        return;
    newLongPollingEvent.ucDestinataire = msg->msg_data[2];
    newLongPollingEvent.ucResourceId = msg->msg_cmd;

    ActiveLongPolling(&newLongPollingEvent);

}

void EmitAnEvent(unsigned char ucResourceId, unsigned char ucDest, unsigned char ucSize, unsigned int unData)
{
    NETV_MESSAGE msg;

    msg.msg_cmd = ucResourceId;
    msg.msg_comm_iface = NETV_COMM_IFAVE_ALL;
    memcpy(&msg.msg_data, &unData, ucSize);
    msg.msg_data_length = ucSize;
    msg.msg_dest = ucDest;
    msg.msg_priority = NETV_PRIORITY_EVENTS;
    msg.msg_remote = 0;
    msg.msg_source = GetMyAddr();
    msg.msg_type = NETV_TYPE_EVENT;
    netv_send_message(&msg);
    
}