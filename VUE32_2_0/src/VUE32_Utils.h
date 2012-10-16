/* 
 * File:   VUE32_Utils.h
 * Author: bedm2308
 *
 * Created on 27 septembre 2012, 10:20
 */

#ifndef VUE32_UTILS_H
#define	VUE32_UTILS_H

#include "NETV32_Common.h"

// Global TimeStamp variable (do not erase!)
extern volatile unsigned int uiTimeStamp;

#define MAX_NBR_LG_PLG 5
#define LIFE_TIME_LONG_POLLING 90000
#define LONG_POLLING_MINIMUM_DELAY 5
#define BMS_HW_INDEX 8

#define ON_MSG_TYPE(type) if (msg->msg_type == type){ unsigned char _temp;
#define ON_MSG_TYPE_RTR(type) if (msg->msg_remote == 1 && msg->msg_type == type){ unsigned char _temp;
#define ANSWER1(ressid, type1, var1)        \
if ( msg->msg_cmd == ressid) {              \
msg->msg_type = msg->msg_type + 1;          \
msg->msg_remote = 0;                        \
_temp = msg->msg_dest;                      \
msg->msg_dest = msg->msg_source;            \
if ( msg->msg_source == 0x3F )              \
    msg->msg_source = GetMyAddr();          \
else                                        \
    msg->msg_source = _temp;                \
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
if ( msg->msg_source == 0x3F )              \
    msg->msg_source = GetMyAddr();          \
else                                        \
    msg->msg_source = _temp;                \
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
if ( msg->msg_source == 0x3F )              \
    msg->msg_source = GetMyAddr();          \
else                                        \
    msg->msg_source = _temp;                \
msg->msg_data_length = sizeof(type1)+sizeof(type2)+sizeof(type3);   \
((type1*)msg->msg_data)[0] = var1;          \
((type2*)(msg->msg_data+sizeof(type1)))[0] = var2;  \
((type3*)(msg->msg_data+sizeof(type1)+sizeof(type2)))[0] = var3;\
netv_send_message(msg);                     \
}

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
var4 = ((type4*)(msg->msg_data+sizeof(type1)+sizeof(type2)+sizeof(type3))[0];

#define END_OF_ACTION }

#define END_OF_MSG_TYPE }

#define EVERY_X_MS(period) \
{static unsigned int _timer = 0; \
if ( _timer < uiTimeStamp ) { \
_timer = uiTimeStamp + period;

#define END_OF_EVERY }}

typedef struct {
    unsigned int unEndWait;
    unsigned int unDelay;
    unsigned char ucResourceId;
    unsigned int unEndPolling;
   unsigned char ucDestinataire;
} LP_PARAMS;

typedef struct {
    unsigned char ucResourceId;
    unsigned char ucDataSize;
    unsigned int unHardwareAddress;
}HDW_MAPPING;

void ActiveLongPolling(LP_PARAMS *sParams);
void DesactivateLongPolling(unsigned char ucRessourceId);
void RunLongPolling();

void ActionStartEmettings(NETV_MESSAGE *msg);


#endif	/* VUE32_UTILS_H */

