/**********************************************************************
 * File : ds18b20cmd.h
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
#ifndef ds18b20cmd_h
#define ds18b20cmd_h


/***********************  ds18b20 Commands ***********************/
#define DS18B20_CMD_CONVERTTEMP			0x44 	/* Convert temperature */

/***********************  OneWire Commands ***********************/
#define ONEWIRE_CMD_RSCRATCHPAD			0xBE
#define ONEWIRE_CMD_WSCRATCHPAD			0x4E
#define ONEWIRE_CMD_CPYSCRATCHPAD		0x48
#define ONEWIRE_CMD_RECEEPROM				0xB8
#define ONEWIRE_CMD_RPWRSUPPLY			0xB4
#define ONEWIRE_CMD_SEARCHROM				0xF0
#define ONEWIRE_CMD_READROM					0x33
#define ONEWIRE_CMD_MATCHROM				0x55
#define ONEWIRE_CMD_SKIPROM					0xCC 


#endif /* ds18b20reg.h */


