/********************************************************************
 FileName:     	usb_config.h
 Dependencies: 	Always: GenericTypeDefs.h, usb_device.h
               	Situational: usb_function_hid.h, usb_function_cdc.h, usb_function_msd.h, etc.
 Company:		Microchip Technology, Inc.

 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the “Company”) for its PIC® Microcontroller is intended and
 supplied to you, the Company’s customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *******************************************************************/

#ifndef _USB_CONFIG_H_
#define _USB_CONFIG_H_

/** DEFINITIONS ****************************************************/
#define USB_EP0_BUFF_SIZE		8
// Valid Options: 8, 16, 32, or 64 bytes.
// Using larger options take more SRAM, but
// does not provide much advantage in most types
// of applications.  Exceptions to this, are applications
// that use EP0 IN or OUT for sending large amounts of
// application related data.
									
#define USB_MAX_NUM_INT     	1   // For tracking Alternate Setting

// Device descriptor - if these two definitions are not defined then
//  a ROM USB_DEVICE_DESCRIPTOR variable by the exact name of device_dsc
//  must exist.
#define USB_USER_DEVICE_DESCRIPTOR &device_dsc
#define USB_USER_DEVICE_DESCRIPTOR_INCLUDE extern ROM USB_DEVICE_DESCRIPTOR device_dsc

// Configuration descriptors - if these two definitions do not exist then
//  a ROM BYTE *ROM variable named exactly USB_CD_Ptr[] must exist.
#define USB_USER_CONFIG_DESCRIPTOR USB_CD_Ptr
#define USB_USER_CONFIG_DESCRIPTOR_INCLUDE extern ROM BYTE *ROM USB_CD_Ptr[]

// PIC32 only suports full ping-pong mode
#define USB_PING_PONG_MODE USB_PING_PONG__FULL_PING_PONG

// Select polled or interrupt-driven operation
//#define USB_POLLING
#define USB_INTERRUPT

/* Parameter definitions are defined in usb_device.h */
#define USB_PULLUP_OPTION USB_PULLUP_ENABLE
//#define USB_PULLUP_OPTION USB_PULLUP_DISABLED

// External transceiver not supported on PIC32
#define USB_TRANSCEIVER_OPTION USB_INTERNAL_TRANSCEIVER

// Low speed not supported for device operation
#define USB_SPEED_OPTION USB_FULL_SPEED

// Operating as a USB device
#define USB_SUPPORT_DEVICE

#define USB_NUM_STRING_DESCRIPTORS 3

//#define USB_INTERRUPT_LEGACY_CALLBACKS
#define USB_ENABLE_ALL_HANDLERS
//#define USB_ENABLE_SUSPEND_HANDLER
//#define USB_ENABLE_WAKEUP_FROM_SUSPEND_HANDLER
//#define USB_ENABLE_SOF_HANDLER
//#define USB_ENABLE_ERROR_HANDLER
//#define USB_ENABLE_OTHER_REQUEST_HANDLER
//#define USB_ENABLE_SET_DESCRIPTOR_HANDLER
//#define USB_ENABLE_INIT_EP_HANDLER
//#define USB_ENABLE_EP0_DATA_HANDLER
//#define USB_ENABLE_TRANSFER_COMPLETE_HANDLER

/** DEVICE CLASS USAGE *********************************************/
#define USB_USE_CDC

/** ENDPOINTS ALLOCATION *******************************************/
#define USB_MAX_EP_NUMBER	    3

/* CDC */
#define CDC_COMM_INTF_ID        0x0
#define CDC_COMM_EP              2
#define CDC_COMM_IN_EP_SIZE      8

#define CDC_DATA_INTF_ID        0x01
#define CDC_DATA_EP             3
#define CDC_DATA_OUT_EP_SIZE    64
#define CDC_DATA_IN_EP_SIZE     64

// Send_Break command
//#define USB_CDC_SUPPORT_ABSTRACT_CONTROL_MANAGEMENT_CAPABILITIES_D2

// Set_Line_Coding, Set_Control_Line_State, Get_Line_Coding, and 
// Serial_State commands
#define USB_CDC_SUPPORT_ABSTRACT_CONTROL_MANAGEMENT_CAPABILITIES_D1

#endif // _USB_CONFIG_H_
