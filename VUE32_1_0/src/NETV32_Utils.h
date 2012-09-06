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

#ifndef _NETV32_UTILS_H_
#define _NETV32_UTILS_H_


//Type definitions
typedef unsigned char uint8;
typedef unsigned int uint16;
typedef char sint8;
typedef int sint16;
typedef unsigned long uint32;
typedef long sint32;
typedef float real32;
typedef double real64;


//MACROS
#define SIGN(val) (val >= 0 ? 1 : -1)
#define ABS(val) (val >= 0 ? val : -val)
#define MIN(val1,val2) (val1 < val2 ? val1 : val2)
#define MAX(val1,val2) (val1 > val2 ? val1 : val2)


#endif
