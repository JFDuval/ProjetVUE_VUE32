/******************************************************************************
 * Board support drivers
 * for initialisation and board specific functions
 * All rights reserved to Projet VUE
 *
 * by Maxime Bedard - 24/09/2012
 * ****************************************************************************/

#ifndef BOARD_H
#define	BOARD_H

/*
 *
 */
typedef enum
{
    ODB = 0x00,
    VUE32_1,
    VUE32_2,
    VUE32_3,
    VUE32_4,
    VUE32_5,
    VUE32_6,
    VUE32_7,
    VUE32_8,
    VUE32_9,
    VUE32_10,
    BMS_1,
    BMS_2,
    BMS_3,
    BMS_4,
    BMS_5,
    BMS_6,
    BMS_7,
    BMS_8,
    BMS_9,
    BMS_10,
    BMS_11,
    BMS_12,
    BMS_13,
    BMS_14,
    BMS_15,
    BMS_16,
    BMS_17,
    BMS_18,
    BMS_19,
    BMS_20,
    BMS_21,
    BMS_22,
    BMS_23,
    BMS_24
} VUE32_ID;

/*
 * Initialize the board
 * Timers, Communication, etc
 * Note : Should only be called once at the begginning of the main
 */
void InitBoard(void);

/*
 * Get the persistent Board Number
 * This value is fixed in flash memory
 */
VUE32_ID GetBoardID(void);

/*
 * Get the firmware version
 */
unsigned short GetFirmVersion(void);

/*
 * Get the current network address of this device
 *  */
unsigned char GetMyAddr(void);

#endif	/* BOARD_H */

