/**********************************************************************
 * File : ds18b20_io.h
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
#ifndef ds18b20_io_h
#define ds18b20_io_h
#include <stdbool.h>
#include <stdint.h>
#include "ds18b20_hw.h"

ds18b20driver_t *ds18b20io_getdriver(void);

#endif /* ds18b20_io.h */
