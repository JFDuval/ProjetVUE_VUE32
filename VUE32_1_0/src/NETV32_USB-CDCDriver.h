/*
The OpenEcoSys project / NETVProtocolStack
Copyright (C) 2011  IntRoLab - Universite de Sherbrooke

Author(s)

Dominic Letourneau, ing., M.Sc.A.
Jean-Francois Duval

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/


#ifndef _NETV32_USB_CDC_DRIVER_H_
#define _NETV32_USB_CDC_DRIVER_H_

//For messages definitions
#include "NETV32_SerialDriver.h"

//USB STUFF
#include "USB-CDC_Microchip\usb.h"
#include "USB-CDC_Microchip\usb_function_cdc.h"
#include "USB-CDC_Microchip\HardwareProfile.h"

void netv32_init_usb_cdc();
void netv32_usb_task();

#endif
