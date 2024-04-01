/**********************************************************************
 * File : ds2482_hw.h
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
#ifndef ds2482_hw_h
#define ds2482_hw_h
#include "ds2482_port.h"


typedef struct
{
    void    (*init)(uint8_t adr);
    bool    (*write_reg)(uint8_t data);
    uint8_t (*read_reg)(void);
}ds2482driver_t;

#endif /* ds2482_hw_h */

