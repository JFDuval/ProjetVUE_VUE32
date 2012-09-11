#ifndef _CAN_BRIDGE_H_
#define _CAN_BRIDGE_H_

#include "def.h"

CANRxMessageBuffer* can_recv_message();
void init_can2();
unsigned short decode_steering_angle(CANRxMessageBuffer* can_data);

#endif
