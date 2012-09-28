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
    VUE32_GENERIC = 0,
    VUE32_1,
    VUE32_2,
    VUE32_3,
    VUE32_4,
    VUE32_5,
    VUE32_6,
    VUE32_7,
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


#endif	/* BOARD_H */

