/* 
 * File:   VUE32_Utils.h
 * Author: bedm2308
 *
 * Created on 27 septembre 2012, 10:20
 */

#ifndef VUE32_UTILS_H
#define	VUE32_UTILS_H

#include "NETV32_Common.h"
#include "def.h"

// Global TimeStamp variable (do not erase!)
extern volatile unsigned int uiTimeStamp;

#define MAX_NBR_LG_PLG 20
#define LIFE_TIME_LONG_POLLING 90000
#define LONG_POLLING_MINIMUM_DELAY 5
#define BMS_HW_INDEX 8
#define LONG_POLLING_WITH_LIFE_TIME 0x01
#define LONG_POLLING_WITHOUT_LIFE_TIME 0x00
#define RESOURCE_ID_MAX_NBR 256

#define ON_MSG_TYPE(type) if (msg->msg_type == type){ unsigned char _temp; _temp = 0x00;
#define ON_MSG_TYPE_RTR(type) if (msg->msg_remote == 1 && msg->msg_type == type){ unsigned char _temp; _temp = 0x00;
#define ANSWER1(ressid, type1, var1)        \
if ( msg->msg_cmd == ressid) {              \
msg->msg_type = msg->msg_type + 1;          \
msg->msg_remote = 0;                        \
_temp = msg->msg_dest;                      \
msg->msg_dest = msg->msg_source;            \
    msg->msg_source = GetMyAddr();          \
msg->msg_data_length = sizeof(type1);       \
((type1*)msg->msg_data)[0] = var1;          \
netv_send_message(msg);                     \
}

#define ANSWER2(ressid, type1, var1, type2, var2)  \
if ( msg->msg_cmd == ressid) {              \
msg->msg_type = msg->msg_type + 1;          \
msg->msg_remote = 0;                        \
_temp = msg->msg_dest;                      \
msg->msg_dest = msg->msg_source;            \
    msg->msg_source = GetMyAddr();          \
msg->msg_data_length = sizeof(type1)+sizeof(type2); \
((type1*)msg->msg_data)[0] = var1;          \
((type2*)(msg->msg_data+sizeof(type1)))[0] = var2;  \
netv_send_message(msg);                     \
}

#define ANSWER3(ressid, type1, var1, type2, var2, type3, var3)  \
if ( msg->msg_cmd == ressid) {              \
msg->msg_type = msg->msg_type + 1;          \
msg->msg_remote = 0;                        \
_temp = msg->msg_dest;                      \
msg->msg_dest = msg->msg_source;            \
    msg->msg_source = GetMyAddr();          \
msg->msg_data_length = sizeof(type1)+sizeof(type2)+sizeof(type3);   \
((type1*)msg->msg_data)[0] = var1;          \
((type2*)(msg->msg_data+sizeof(type1)))[0] = var2;  \
((type3*)(msg->msg_data+sizeof(type1)+sizeof(type2)))[0] = var3;\
netv_send_message(msg);                     \
}

#define ANSWER4(ressid, type1, var1, type2, var2, type3, var3, type4, var4)  \
if ( msg->msg_cmd == ressid) {              \
msg->msg_type = msg->msg_type + 1;          \
msg->msg_remote = 0;                        \
_temp = msg->msg_dest;                      \
msg->msg_dest = msg->msg_source;            \
    msg->msg_source = GetMyAddr();          \
msg->msg_data_length = sizeof(type1)+sizeof(type2)+sizeof(type3)+sizeof(type4);   \
((type1*)msg->msg_data)[0] = var1;          \
((type2*)(msg->msg_data+sizeof(type1)))[0] = var2;  \
((type3*)(msg->msg_data+sizeof(type1)+sizeof(type2)))[0] = var3; \
((type4*)(msg->msg_data+sizeof(type1)+sizeof(type2)+sizeof(type3)))[0] = var4; \
netv_send_message(msg);                     \
}

#define SYNC1(ressid, type1, var1)        \
{              \
msg->msg_type = 0x02;          \
msg->msg_remote = 0;                        \
msg->msg_cmd = ressid;                      \
_temp = msg->msg_dest;                      \
msg->msg_dest = 0x05;            \
    msg->msg_source = GetMyAddr();          \
msg->msg_data_length = sizeof(type1);       \
((type1*)msg->msg_data)[0] = var1;          \
netv_send_message(msg);                     \
}

#define ACTION0(ressid) \
if ( msg->msg_cmd == ressid) {

#define ACTION1(ressid, type1, var1) \
if ( msg->msg_cmd == ressid && msg->msg_data_length >= sizeof(type1)) {   \
var1 = ((type1*)msg->msg_data)[0];

#define ACTION2(ressid, type1, var1, type2, var2) \
if ( msg->msg_cmd == ressid && msg->msg_data_length >= sizeof(type1)+sizeof(type2)) {   \
var1 = ((type1*)msg->msg_data)[0];          \
var2 = ((type2*)(msg->msg_data+sizeof(type1)))[0];

#define ACTION3(ressid, type1, var1, type2, var2, type3, var3) \
if ( msg->msg_cmd == ressid && msg->msg_data_length >= sizeof(type1)+sizeof(type2)+sizeof(type3)) {   \
var1 = ((type1*)msg->msg_data)[0];          \
var2 = ((type2*)(msg->msg_data+sizeof(type1)))[0];  \
var3 = ((type3*)(msg->msg_data+sizeof(type1)+sizeof(type2)))[0];

#define ACTION4(ressid, type1, var1, type2, var2, type3, var3, type4, var4) \
if ( msg->msg_cmd == ressid && msg->msg_data_length >= sizeof(type1)+sizeof(type2)+sizeof(type3)+sizeof(type4)) {   \
var1 = ((type1*)msg->msg_data)[0];          \
var2 = ((type2*)(msg->msg_data+sizeof(type1)))[0];  \
var3 = ((type3*)(msg->msg_data+sizeof(type1)+sizeof(type2)))[0];    \
var4 = ((type4*)(msg->msg_data+sizeof(type1)+sizeof(type2)+sizeof(type3)))[0];

#define END_OF_ACTION }

#define END_OF_MSG_TYPE }

#define EVERY_X_MS(period) \
{static unsigned int _timer = 0; \
if ( _timer < uiTimeStamp ) { \
_timer = uiTimeStamp + period;

#define EVERY_X_MS2(period, offset) \
{static unsigned int _timer = offset; \
if ( _timer < uiTimeStamp ) { \
_timer = uiTimeStamp + period;

#define END_OF_EVERY }}

#define BLOCK_X_MS(delay) \
{ unsigned int _timer = uiTimeStamp + delay; \
while (uiTimeStamp < _timer); \
}

typedef struct {
    unsigned int unEndWait;
    unsigned int unDelay;
    unsigned char ucResourceId;
    unsigned int unEndPolling;
    unsigned char ucDestinataire;
    unsigned char hasLifeTime;
    unsigned char ucSizeData;
    unsigned char ucMsgType;
    unsigned char ucVUE32Addr;
} LP_PARAMS;

typedef struct {
    unsigned char ucResourceId;
    unsigned char ucDataSize;
    BOOL bIsSensor;
}HDW_MAPPING;

void ActiveLongPolling(LP_PARAMS *sParams);
void DesactivateLongPolling(unsigned char ucRessourceId);
void RunLongPolling();

void ActionStartEmettings(NETV_MESSAGE *msg);

//Set the value at distance on the other VUE32. Then, drivers function can use it as the sensor is local
void CopyValueOn(unsigned char ucDest, unsigned char ucResourceId, unsigned int unDelay);

void EmitAnEvent(unsigned char ucResourceId, unsigned char ucDest, unsigned char ucSize, unsigned int unData);
void CopyValueFromDistantVUE32(NETV_MESSAGE *msg);
void SetResourceValue(unsigned char ucResourceId, unsigned char ucDest, unsigned char ucSize, unsigned int unData);


#endif	/* VUE32_UTILS_H */

