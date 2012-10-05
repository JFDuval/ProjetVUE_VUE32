#include "VUE32_Utils.h"
#include "NETV32_Common.h"
#include "def.h"

LP_PARAMS g_sLpParams[MAX_NBR_LG_PLG];
unsigned int g_unLpSize = 0;

//Incremented by interrupt each 1 ms
volatile unsigned int uiTimeStamp;


void ActiveLongPolling(LP_PARAMS *sParams)
{
    if ( g_unLpSize == MAX_NBR_LG_PLG || sParams == NULL)
        return;

    //TODO Verify if the ressource id exist in the board context. If it isn't the case, the function must return immediatly

    //Make the ressource id doesn't exist already in the static array
    unsigned int i;
    for(i = 0; i< MAX_NBR_LG_PLG; i++)
    {
        if(g_sLpParams[i].ucResourceId == sParams->ucResourceId)
            return;
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

void RunLongPolling()
{
    //For each subcribed sensor to long polling event
    unsigned int i;
    for(i = 0; i<g_unLpSize; i++)
    {
        //Check if it's time to send the sensor's value
        if(g_sLpParams[i].unEndWait <= uiTimeStamp)
        {
            NETV_MESSAGE msg;
            msg.msg_priority = NETV_PRIORITY_EVENTS;
            msg.msg_type = NETV_TYPE_EVENT;
            msg.msg_cmd = g_sLpParams[i].ucResourceId;
            msg.msg_source = GetMyAddr();
            msg.msg_dest = 0x00;
            //TODO Link with the application who's interfaced with the hardware layer
            //msg.msg_data_length = g_sLpParams[i]->NbrByte;
            //memcpy(&msg.msg_data, TODO, g_sLpParams[i]->NbrByte);
            netv_send_message(&msg);
        }
        
        //Check for the sensor's life time
        if(g_sLpParams[i].unEndPolling <= uiTimeStamp)
        {
            //Desactivating the long polling for it
            DesactivateLongPolling(g_sLpParams[i].ucResourceId);
        }
    }
}