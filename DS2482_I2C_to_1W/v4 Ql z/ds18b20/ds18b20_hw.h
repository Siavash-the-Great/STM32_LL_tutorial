/**********************************************************************
 * File : ds18b20_hw.h
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
#ifndef ds18b20_hw_h
#define ds18b20_hw_h
#include "ds18b20_port.h"


typedef struct
{
    void    (*init)				(void);
    void    (*reset)			(void);
		bool		(*write_byte)	(uint8_t);
    uint8_t (*read_byte)	(void);
}ds18b20driver_t;

#endif /* ds18b20_hw_h */
