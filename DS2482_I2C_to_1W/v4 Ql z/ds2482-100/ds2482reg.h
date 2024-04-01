/**********************************************************************
 * File : ds2482reg.h
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
#ifndef ds2482reg_h
#define ds2482reg_h

#define DS2482_ADDRESS								(0x30)

/*****************  address of registers *****************/
#define DS2482_REG_STATUS							(0xF0)	// 1
#define DS2482_REG_READ_DATA					(0xE1)	// 2 
#define DS2482_REG_CONFIGURATION			(0xC3)	// 3

/***********************  Commands ***********************/
#define DS2482_CMD_DEVICE_RESET					0xF0
#define DS2482_CMD_SET_READ_POINTER			0xE1
#define DS2482_CMD_WRITE_CONFIGURATION	0xD2
#define DS2482_CMD_ONE_WIRE_RESET				0xB4
#define DS2482_CMD_ONE_WIRE_SINGLE_BIT	0x87
#define DS2482_CMD_ONE_WIRE_WRITE_BYTE	0xA5
#define DS2482_CMD_ONE_WIRE_READ_BYTE		0x96
#define DS2482_CMD_ONE_WIRE_TRIPLET			0x78	






#endif /* ds2482reg.h */


