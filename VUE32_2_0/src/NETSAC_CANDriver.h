#ifndef NETSAC_CANDRIVER_H
#define NETSAC_CANDRIVER_H

#include "plib.h"
#include "drive.h"

#define MIN(val1,val2) (val1 < val2 ? val1 : val2)

unsigned char CanNETSACRxMessage(DRIVE_MSG *message, CAN_MODULE CANx);
unsigned char CanNETSACTxMessage(DRIVE_MSG *message, CAN_MODULE CANx);


#endif