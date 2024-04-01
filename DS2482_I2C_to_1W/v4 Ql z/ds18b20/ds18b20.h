/**********************************************************************
 * File : ds18b20.h
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
#ifndef ds18b20_h
#define ds18b20_h

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "ds18b20cmd.h"
#include "ds18b20_hw.h"
#include "ds18b20_io.h"
#include "Ql_IIC.h"

typedef struct
{
	ds18b20driver_t *interface;
}ds18b20_t;

ds18b20_t *ds18b20_init(ds18b20driver_t *hw);

float	DS2482_DS18B20_Convert(ds18b20_t *temp_ptr);
#endif /* ds18b20_h */

