/**********************************************************************
 * File : ds2482.h
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
#ifndef ds2482_h
#define ds2482_h

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "ds2482reg.h"
#include "ds2482_hw.h"
#include "ds2482_io.h"

typedef struct
{
	ds2482driver_t *interface;
}ds2482_t;

ds2482_t *ds2482_init(ds2482driver_t *hw, uint8_t address);

#endif /* ds2482_h */

