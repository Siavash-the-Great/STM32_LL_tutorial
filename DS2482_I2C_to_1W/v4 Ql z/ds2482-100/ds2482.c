/**********************************************************************
 * File : ds2482.c
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
#include "ds2482.h"
#include "ds2482_io.h"	//
#include "ds2482_port.h"



ds2482_t *ds2482_init(ds2482driver_t *hw,uint8_t address)
{
    /*check hw ptr*/
    if(!hw)
        return NULL;

    /*validate hw functions*/
    if(!hw->read_reg || !hw->init || !hw->write_reg)
        return NULL;

    /*create adxl obj*/
//    ds2482_t *ptr = ds2482_malloc(sizeof(ds2482_t));
    ds2482_t *ptr = malloc(sizeof(ds2482_t));
    /*validate ptr*/
    if(!ptr)
        return NULL;
    
    /*set up pointer*/
    ptr->interface = hw;
    ptr->interface->init(address);
    
    return ptr;
}



