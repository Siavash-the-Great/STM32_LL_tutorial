/**********************************************************************
 * File : ds18b20.c
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
#include "ds18b20.h"
#include "ds18b20_io.h"	//
#include "ds18b20_port.h"



ds18b20_t *ds18b20_init(ds18b20driver_t *hw)
{
    /*check hw ptr*/
    if(!hw)
        return NULL;

    /*validate hw functions*/
    if(!hw->init || !hw->reset || !hw->write_byte || !hw->read_byte)
        return NULL;

    /*create adxl obj*/
//    ds18b20_t *ptr = ds18b20_malloc(sizeof(ds18b20_t));
		ds18b20_t *ptr = malloc(sizeof(ds18b20_t));	    
    /*validate ptr*/
    if(!ptr)
        return NULL;
    
    /*set up pointer*/
    ptr->interface = hw;
    ptr->interface->init();
    
    return ptr;
}


//--------------------------------------------------------------------------
// Send 8 bits of communication to the 1-Wire Net and return the
// result 8 bits read from the 1-Wire Net. The parameter 'sendbyte'
// least significant 8 bits are used and the least significant 8 bits
// of the result are the return byte.
//
// 'sendbyte' - 8 bits to send (least significant byte)
//
// Returns:  8 bits read from sendbyte
//
unsigned char OWTouchByte(ds18b20_t *temp_ptr, unsigned char sendbyte)
{
   if (sendbyte == 0xFF)
   {
      return temp_ptr->interface->read_byte();	
   }
   else
	{
      temp_ptr->interface->write_byte(sendbyte);	
      return sendbyte;
	}
}

//--------------------------------------------------------------------------
// The 'OWBlock' transfers a block of data to and from the
// 1-Wire Net. The result is returned in the same buffer.
//
// 'tran_buf' - pointer to a block of unsigned
//              chars of length 'tran_len' that will be sent
//              to the 1-Wire Net
// 'tran_len' - length in bytes to transfer
//
void OWBlock(ds18b20_t *temp_ptr, unsigned char *tran_buf, int tran_len)
{
   int i;

   for (i = 0; i < tran_len; i++)
      tran_buf[i] = OWTouchByte(temp_ptr, tran_buf[i]);
}

//--------------------------------------------------------------------------
float	DS2482_DS18B20_Convert(ds18b20_t *temp_ptr)
{
	unsigned char data[2] = {0xFF, 0xFF};

	temp_ptr->interface->reset();
	temp_ptr->interface->write_byte(ONEWIRE_CMD_SKIPROM);
	temp_ptr->interface->write_byte(DS18B20_CMD_CONVERTTEMP);

	Delay_msec(375);

	temp_ptr->interface->reset();
	
	temp_ptr->interface->write_byte(ONEWIRE_CMD_SKIPROM);
	temp_ptr->interface->write_byte(ONEWIRE_CMD_RSCRATCHPAD);

	OWBlock(temp_ptr, data, 2);
	
	uint16_t fpTemperature = (((uint16_t) data[1]) << 11)
	| (((uint16_t) data[0]) << 3);
	

	return (float) fpTemperature * 0.0078125;
}
