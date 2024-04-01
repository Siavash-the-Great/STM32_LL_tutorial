/**********************************************************************
 * File : ds2482_io.c
 * Copyright (c) Moustachioed.
 * Created On : Sat Jun 18 2022
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 **********************************************************************/

//#include <DebugTask.h>

#include "ds2482_io.h"
//#include "iic_interface.h"
#include "Ql_IIC.h"
//#include <ql_stdlib.h>
#include <stdlib.h>
#include "ds2482reg.h"
//#include <ql_memory.h>

//#define debug(...)          debugf(Window14,__VA_ARGS__)
//#define Errdebug(...)		debugf(Window24,__VA_ARGS__)

static uint8_t ds2482adr = 0;

void ds2482io_init(uint8_t adr)
{
    ds2482adr = adr;
}

uint8_t ds2482io_oneByteRead(void)
{
	u8 inst_buf[1] = {DS2482_CMD_ONE_WIRE_READ_BYTE};
	if(Ql_IIC_Write(0, ds2482adr, inst_buf, 1) < 0)
;//		Errdebug("can not read ds2482 register");
 
 	u8 inst_buf2[2] = {DS2482_CMD_SET_READ_POINTER, DS2482_REG_READ_DATA};
    if(Ql_IIC_Write(0, ds2482adr, inst_buf2, 2) < 0)
;//        Errdebug("can not read ds2482 register");

	u8 data = {0x00};
    if(Ql_IIC_Read(0, ds2482adr, &data, 1) < 0)
;//        Errdebug("can not read ds2482 register");
		
	return data;
}

bool ds2482io_oneByteWrite(uint8_t Data)
{
	u8 inst_buf[2] = {DS2482_CMD_ONE_WIRE_WRITE_BYTE, Data};
    if(Ql_IIC_Write(0, ds2482adr, inst_buf, 2) < 0)
        return false;
    return true;
}

ds2482driver_t *ds2482io_getdriver(void)
{
//    ds2482driver_t *ptr = Ql_MEM_Alloc(sizeof(ds2482driver_t));
		ds2482driver_t *ptr = malloc(sizeof(ds2482driver_t));
    if(!ptr)
        return NULL;
    ptr->init = ds2482io_init;
    ptr->write_reg = ds2482io_oneByteWrite;
    ptr->read_reg = ds2482io_oneByteRead;
    return ptr;
}

