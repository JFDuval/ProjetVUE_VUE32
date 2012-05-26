
/*
The OpenEcoSys project / NETVProtocolStack
Copyright (C) 2011  IntRoLab - Universite de Sherbrooke

Author(s)

Dominic Letourneau, ing., M.Sc.A.

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

#ifndef _NETV32_NETV_DRIVER_H_
#define _NETV32_NETV_DRIVER_H_

#include "NETV32_Shared.h"
#include "NETV32_Device.h"
#include "NETV32_Common.h"

typedef struct _filter {
   unsigned char filter_priority;
   unsigned char filter_type;
   unsigned char filter_cmd;
   unsigned char filter_dest;
} NETV_FILTER;

typedef struct _mask {
   unsigned char mask_priority;
   unsigned char mask_type;
   unsigned char mask_cmd;
   unsigned char mask_dest;
} NETV_MASK;

//Hardware specific
void netv_init_can_driver(NETV_FILTER *filter,NETV_MASK *mask);
void netv_apply_accept_mask(NETV_MASK *mask, unsigned char mask_id);
void netv_apply_filter(NETV_FILTER *filter, unsigned char filter_id);



#endif
