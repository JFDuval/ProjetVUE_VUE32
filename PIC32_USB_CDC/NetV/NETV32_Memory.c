/*
The OpenEcoSys project / CANProtocolStack
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

#include "NETV32_Memory.h"
#include "NETV32_Common.h"
#include "bsp.h"


#ifdef USE_EEPROM
int __attribute__ ((space(eedata))) eeData = BOOT_NORMAL; // Variable located in EEPROM  //Used as the base address
#endif

unsigned int WriteMem(unsigned int offset, unsigned int* dataPtr, unsigned int size)
{
	while(size--)
	{
		ee_word_write(offset, (*dataPtr++));
		offset += 2;	//1 word
	}
	return 0;
}

unsigned long ReadMem(unsigned int offset)
{
	return ee_word_read(offset);
}



void ee_word_write(unsigned int offset, int data)
{
#ifdef USE_EEPROM
	_prog_addressT p;
	_init_prog_address(p, eeData);
	p += offset;
	asm volatile ("disi #5"); // Disable Interrupts For 5 Instructions (TODO, validate the number of cycles)
	_erase_eedata(p,_EE_WORD);	
	_wait_eedata();
	asm volatile ("disi #5"); // Disable Interrupts For 5 Instructions (TODO, validate the number of cycles)
	_write_eedata_word(p,data);	
	_wait_eedata();
#else
#warning "ee_word_write NOT using EEPROM, Flash implementation not available"
#endif
}


int ee_word_read(unsigned int offset)
{
#ifdef USE_EEPROM
	int data = 0;
	_prog_addressT p;
	_init_prog_address(p, eeData);
	p += offset;
	_memcpy_p2d16(&data, p, 1);
	return data;
#else
	#warning "ee_word_read NOT using EEPROM, Flash implementation not available"
	return 0;
#endif
}
