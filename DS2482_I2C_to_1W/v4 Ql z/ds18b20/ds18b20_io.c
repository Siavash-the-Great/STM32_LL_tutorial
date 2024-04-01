/**********************************************************************
 * File : ds18b20_io.c
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
#include "ds2482.h"
#include "ds18b20_io.h"
//#include "iic_interface.h"
#include "Ql_IIC.h" 
#include "ds18b20.h"
#include "ds2482reg.h"
//#include <ql_stdlib.h>
#include <stdlib.h>
//#include <ql_memory.h>

//#define debug(...)          debugf(Window14,__VA_ARGS__)
//#define Errdebug(...)		debugf(Window24,__VA_ARGS__)

//static uint8_t ds18b20adr = 0;
	ds2482driver_t *convhw;
	ds2482_t *conv_ptr;
	
void ds18b20io_init(void)
{
		convhw = ds2482io_getdriver();
    conv_ptr = ds2482_init(convhw, 0x30);
}

void ds18b20io_reset(void)
{
    u8 inst_buf[1] = {DS2482_CMD_ONE_WIRE_RESET};
   	Ql_IIC_Write(0, I2C_Slave_Adr, inst_buf, 1);
}

uint8_t ds18b20io_oneByteRead(void)
{
    return conv_ptr->interface->read_reg();
}

bool ds18b20io_oneByteWrite(uint8_t Data)
{
	return conv_ptr->interface->write_reg(Data);
}

ds18b20driver_t *ds18b20io_getdriver(void)
{
 //   ds18b20driver_t *ptr = Ql_MEM_Alloc(sizeof(ds18b20driver_t));
	ds18b20driver_t *ptr = malloc(sizeof(ds18b20driver_t));
    if(!ptr)
        return NULL;
  ptr->init = ds18b20io_init;
	ptr->reset = ds18b20io_reset;
  ptr->write_byte = ds18b20io_oneByteWrite;
  ptr->read_byte = ds18b20io_oneByteRead;
  return ptr;
}



// bool adxlio_multiByteRead(int startAddress, char* buffer, int size)
// {
//     uint8_t reg_adr[1] = {startAddress};
//     if(IIC_Write_Read(adxladr,reg_adr,1,(uint8_t*)buffer,size)==false)
//         return false;
//     return true;
// }

// bool adxlio_multiByteWrite(int startAddress, char* buffer, int size)
// {
//     uint8_t WriteByte[size+1];
//     WriteByte[0] = startAddress;
//     Ql_memcpy(WriteByte+1,buffer,size);
//     if(IIC_Write(adxladr,WriteByte,size+1)==false)
//         return false;
//     return true;
// }

// uint8_t adxlio_getid(void)
// {
//     return adxlio_oneByteRead(0x00);
// }

