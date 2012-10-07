/* 
 * File:   communication.h
 * Author: bedm2308
 *
 * Created on 21 septembre 2012, 15:53
 */

#ifndef COMMUNICATION_H
#define	COMMUNICATION_H

#include "NETV32_Common.h"
#include "Board.h" //Todo: remove this include, and put it in the .c files that need it

// Send the message through the selected interfaces
unsigned char netv_send_message (NETV_MESSAGE *message);

// Receive a message from any interface (and set the corresponding flag)
unsigned char netv_recv_message (NETV_MESSAGE *message);


#endif	/* COMMUNICATION_H */

