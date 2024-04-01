/**********************************************************************
 * File : ds2482_io.h
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
#ifndef ds2482_io_h
#define ds2482_io_h

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include "ds2482_hw.h"

ds2482driver_t *ds2482io_getdriver(void);

#endif /* ds2482_io.h */

