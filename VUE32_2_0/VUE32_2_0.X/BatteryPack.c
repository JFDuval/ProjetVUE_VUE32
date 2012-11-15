/*
 * Implementation of the battery pack logic
 *
 */

#include "BatteryPack.h"
#include "../src/NETV32_Utils.h"

#define NUMBER_OF_BMS 24
#define NUMBER_OF_CELLS 8
#define TEMPERATURE_MAX_CELL                500                     //Temperature maximale des cellules 50.0°C
#define TEMPERATURE_MAX_RES                 800                     //Temperature maximale des résistances  90.0°C

#define TENSION_MAX_CELL					3600 			// Tension maximale pour activer le fet ne pas dépasser 4200 Doit être ajusté selon le type de cellule
#define TENSION_MIN_CELL                    2400
#define GAP_OVER_MIN_CELL					20			// Gap de tension avec la plus basse tension
#define TENSION_START_FET					3200		// Tension minimal pour activer le FET
#define TENSION_MAX_OPEN_CONTACTOR          3650        // Tension ou les contacteurs ouvrent

#define BMS_TIMEOUT_COMM_MS                 500

// Extern variables
extern volatile unsigned int uiTimeStamp;

// Static variables
E_BMS_STATES eCurrentReqState;
unsigned short usReqTension;
E_BMS_STATES eBMSState[NUMBER_OF_BMS];
unsigned int unTimestampLastMsg[NUMBER_OF_BMS];
unsigned short usCellTension[NUMBER_OF_BMS][NUMBER_OF_CELLS];
unsigned short usMaxResTemp;
unsigned short usMaxCellTemp;
unsigned short usNumberConnectedBMS;
unsigned char fBMSError;

// Local function for openning the contactor
void OpenContactor()
{
    static unsigned int _timer = 0;
    fBMSError = 1;
    if ( _timer < uiTimeStamp )  // Throttle the error messages, no more than 10/s (the first one is instantaneous)
    {
        _timer = uiTimeStamp + 250;
        NETV_MESSAGE oMsg;
        oMsg.msg_cmd = E_ID_MAIN_CONTACTOR;
        oMsg.msg_comm_iface = NETV_COMM_IFACE_CAN1;
        oMsg.msg_data_length = 1;
        oMsg.msg_data[0] = 0;
        oMsg.msg_dest = 0x03;
        oMsg.msg_priority = NETV_PRIORITY_HIGHEST;
        oMsg.msg_remote = 0;
        oMsg.msg_source = GetMyAddr();
        oMsg.msg_type = VUE32_TYPE_SETVALUE;
        netv_send_message(&oMsg);
        /*
         TODO: Very important, we have to close the contactor here and send the error to the OdB
         */
    }
}

// Initialize state machine for the battery pack
void InitBatteryPack()
{
    // Initialisation
    unsigned int i,j;
    for (i=0; i<NUMBER_OF_BMS; i++)
    {
        eBMSState[i] = noComm;
        unTimestampLastMsg[i] = 0;
        for(j=0; j<NUMBER_OF_CELLS; j++)
            usCellTension[i][j] = 0;
    }
    usMaxResTemp = 0;
    usMaxCellTemp = 0;
    usNumberConnectedBMS = 0;
    fBMSError = 0;
    eCurrentReqState = Monitor;
}

// Run the battery pack state machine
void RunBatteryPack()
{
    // Check for Comm Lost event
    unsigned int i, j, numConnBMS = 0, minTension = 0xFFFF, maxTension = 0;
    for ( i=0; i<NUMBER_OF_BMS; i++ )
    {
        if( eBMSState[i] != noComm && unTimestampLastMsg[i] + BMS_TIMEOUT_COMM_MS < uiTimeStamp )
        {
            // Communication with this BMS just died, we should probably stop everything
            eBMSState[i] = noComm;
            OpenContactor();
            break;
        }
        else if ( eBMSState[i] != noComm && eBMSState[i] != Connecting )
        {
            numConnBMS += 1;
        }
    }
    usNumberConnectedBMS = numConnBMS;

    // Make sure all tensions are inside the limits
    for ( i=0; i<NUMBER_OF_BMS; i++ )
    {
        for ( j=0; j<NUMBER_OF_CELLS; j++ )
        {
            if ( minTension > usCellTension[i][j] )
                minTension = usCellTension[i][j];
            if ( maxTension < usCellTension[i][j] )
                maxTension = usCellTension[i][j];
        }
    }
    if ( minTension < TENSION_MIN_CELL || maxTension > TENSION_MAX_OPEN_CONTACTOR)
    {
        OpenContactor();
    }

    // Refresh all data every second
    static unsigned int _timer = 0;
    static unsigned short rotation = 0;
    if ( _timer < uiTimeStamp ) 
    {
        NETV_MESSAGE oMsg;
        _timer = uiTimeStamp + 250;
        switch(rotation)
        {
        case 0: // TOdo: mettre des defines
            oMsg.msg_cmd = 0x14;
            break;
        case 1:
            oMsg.msg_cmd = 0x15;
            break;
        case 2:
            oMsg.msg_cmd = 0x16;
            break;
        case 3:
            oMsg.msg_cmd = 0x17;
        }

        rotation += 1;
        if (rotation > 3)
            rotation = 0;

        oMsg.msg_comm_iface = NETV_COMM_IFACE_CAN2;
        oMsg.msg_data_length = 0;
        oMsg.msg_dest = 0xFF;
        oMsg.msg_priority = 0;
        oMsg.msg_remote = 0;
        oMsg.msg_source = GetMyAddr();
        oMsg.msg_type = VUE32_TYPE_GETVALUE;
        netv_send_message(&oMsg);
    }

}

// Interpretation of BMS messages
void OnBatteryMsg(NETV_MESSAGE *msg)
{
    if ( msg->msg_source > 0x10 && msg->msg_source < 0x29 )
    {
        unsigned int bmsId = msg->msg_source - 0x11; // BMS 0 to 24

        unTimestampLastMsg[bmsId] = uiTimeStamp;

        if ( msg->msg_cmd == 0x14 && msg->msg_data_length >= 2 ) // E_ID_BMS_BOARD_TEMP
        {
            unsigned short temp = *((unsigned short*)msg->msg_data);
            if ( usMaxResTemp < temp)
            {
                // Only keep the maximum temperature
                usMaxResTemp = temp;
                if ( usMaxResTemp > TEMPERATURE_MAX_RES )
                {
                    // Resistors too hot, stop balancing
                    eCurrentReqState = Monitor;
                    if ( usMaxResTemp > TEMPERATURE_MAX_RES + 100)
                    {
                        // More safety, open the contactor
                        OpenContactor();
                    }
                }
            }
        }
        else if ( (msg->msg_cmd == 0x17 ||  msg->msg_cmd == 0x1E) && msg->msg_data_length >= 2 ) // State
        {
            // Read the BMS State
            unsigned short temp = *((unsigned short*)msg->msg_data);
            if ( eBMSState[bmsId] == noComm )
                eBMSState[bmsId] = Connecting;
            else
                eBMSState[bmsId] = (E_BMS_STATES)temp;

            // Check for "ProblemDetected" state
            if ( eBMSState[bmsId] == ProblemDetected )
            {
                // Stop everything
                OpenContactor();
            }
            
            // Make sure the right state is setted
            if ( (eCurrentReqState == Monitor && eBMSState[bmsId] == Balance) || (eCurrentReqState == Balance && eBMSState[bmsId] == Monitor) )
            {
                NETV_MESSAGE oMsg;
                oMsg.msg_cmd = E_ID_BMS_STATE_READONLY;
                oMsg.msg_type = VUE32_TYPE_SETVALUE;
                oMsg.msg_comm_iface = NETV_COMM_IFACE_CAN2;
                oMsg.msg_remote = 0;
                oMsg.msg_source = GetMyAddr();
                oMsg.msg_dest = 0xFF;

                if ( eCurrentReqState== Balance)
                {
                    // Send the command right now
                    oMsg.msg_data_length = 6;
                    ((unsigned short*)oMsg.msg_data)[0] = (unsigned short)Balance;
                    ((unsigned short*)oMsg.msg_data)[1] = (unsigned short)1;
                    ((unsigned short*)oMsg.msg_data)[2] = usReqTension;
                    netv_send_message(&oMsg);
                }
                else
                {
                    // Send the command right now
                    oMsg.msg_data_length = 2;
                    ((unsigned short*)oMsg.msg_data)[0] = (unsigned short)Monitor;
                    netv_send_message(&oMsg);
                }
            }
        }
        else if ( msg->msg_cmd == 0x15 && msg->msg_data_length >= 6 ) // E_ID_BMS_CELL_GROUP1
        {
            unsigned short temp = *((unsigned short*)msg->msg_data);
            if ( temp == 0)
            {
                usCellTension[bmsId][0] = *((unsigned short*)(msg->msg_data+2)); //cellTension[0]
                usCellTension[bmsId][1] = *((unsigned short*)(msg->msg_data+4)); //cellTension[1]
                temp = *((unsigned short*)(msg->msg_data+4)); // deviceTemp[0]
                if ( temp > usMaxCellTemp)
                    usMaxCellTemp = temp;

                // Check all these values
                if ( usMaxCellTemp > TEMPERATURE_MAX_CELL )
                {
                    OpenContactor();
                }
            }
            else
            {
                usCellTension[bmsId][2] = *((unsigned short*)(msg->msg_data+2)); //cellTension[2]
                usCellTension[bmsId][3] = *((unsigned short*)(msg->msg_data+4)); //cellTension[3]
            }
        }
        else if ( msg->msg_cmd == 0x16 && msg->msg_data_length >= 2 ) // E_ID_BMS_CELL_GROUP2
        {
            unsigned short temp = *((unsigned short*)msg->msg_data);
            if ( temp == 0)
            {
                usCellTension[bmsId][4] = *((unsigned short*)(msg->msg_data+2)); //cellTension[4]
                usCellTension[bmsId][5] = *((unsigned short*)(msg->msg_data+4)); //cellTension[5]
                temp = *((unsigned short*)(msg->msg_data+4)); // deviceTemp[0]
                if ( temp > usMaxCellTemp)
                    usMaxCellTemp = temp;

                // Check all these values
                if ( usMaxCellTemp > TEMPERATURE_MAX_CELL )
                {
                    OpenContactor();
                }
            }
            else
            {
                usCellTension[bmsId][6] = *((unsigned short*)(msg->msg_data+2)); //cellTension[6]
                usCellTension[bmsId][7] = *((unsigned short*)(msg->msg_data+4)); //cellTension[7]
            }
        }
    }
}

// Change the state of the whole battery pack
void SetState(E_BMS_STATES eState)
{
    if ( eState == Balance )
    {
        // We have to find the minimum tension of the pack
        unsigned int i,j;
        unsigned short minCellTension = 0xFFFF;
        for (i=0; i<NUMBER_OF_BMS; i++)
        {
            if ( eBMSState[i] != noComm && eBMSState[i] != Connecting )
            {
                for(j=0; j<NUMBER_OF_CELLS; j++)
                {
                    if ( minCellTension > usCellTension[i][j] )
                        minCellTension = usCellTension[i][j];
                }
            }
        }

        if ( minCellTension != 0xFF && minCellTension > TENSION_START_FET )
        {
            usReqTension = minCellTension;
            eCurrentReqState = eState;

            // Send the command right now
            NETV_MESSAGE oMsg;
            oMsg.msg_cmd = E_ID_BMS_STATE_READONLY;
            oMsg.msg_type = VUE32_TYPE_SETVALUE;
            oMsg.msg_comm_iface = NETV_COMM_IFACE_CAN2;
            oMsg.msg_data_length = 6;
            ((unsigned short*)oMsg.msg_data)[0] = (unsigned short)Balance;
            ((unsigned short*)oMsg.msg_data)[1] = (unsigned short)1;
            ((unsigned short*)oMsg.msg_data)[2] = usReqTension;
            oMsg.msg_remote = 0;
            oMsg.msg_source = GetMyAddr();
            oMsg.msg_dest = 0xFF;
            netv_send_message(&oMsg);
        }
    }
    else if ( eState == Monitor )
    {
        // Send the command right now
        NETV_MESSAGE oMsg;
        oMsg.msg_cmd = E_ID_BMS_STATE_READONLY;
        oMsg.msg_type = VUE32_TYPE_SETVALUE;
        oMsg.msg_comm_iface = NETV_COMM_IFACE_CAN2;
        oMsg.msg_data_length = 2;
        ((unsigned short*)oMsg.msg_data)[0] = (unsigned short)Monitor;
        oMsg.msg_remote = 0;
        oMsg.msg_source = GetMyAddr();
        oMsg.msg_dest = 0xFF;
        netv_send_message(&oMsg);

        eCurrentReqState = eState;
    }
}

// Get number of currently connected BMS
unsigned short GetNumConnectedBMS()
{
    return usNumberConnectedBMS;
}

