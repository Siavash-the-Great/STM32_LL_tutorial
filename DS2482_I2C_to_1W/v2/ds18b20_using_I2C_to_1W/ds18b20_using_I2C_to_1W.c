/**
  ******************************************************************************
  * @file		ds18b20_using_I2C_to_1W.c
  ******************************************************************************
  */

 
/********************/
/********///includes: 

	#include "ds18b20_using_I2C_to_1W.h"
/********************/
/********///definitions:

/***********************  Commands ***********************/

#define DS18B20_CMD_CONVERTTEMP			0x44 	/* Convert temperature */
/* OneWire commands */
#define ONEWIRE_CMD_RSCRATCHPAD			0xBE
#define ONEWIRE_CMD_WSCRATCHPAD			0x4E
#define ONEWIRE_CMD_CPYSCRATCHPAD		0x48
#define ONEWIRE_CMD_RECEEPROM				0xB8
#define ONEWIRE_CMD_RPWRSUPPLY			0xB4
#define ONEWIRE_CMD_SEARCHROM				0xF0
#define ONEWIRE_CMD_READROM					0x33
#define ONEWIRE_CMD_MATCHROM				0x55
#define ONEWIRE_CMD_SKIPROM					0xCC  	


/********************/
/********///Functions:  

float	DS2482_DS18B20_Convert(void)
{
	unsigned char data[2] = {0xFF,0xFF};

	DS2482_1W_Reset();
	DS2482_1Wire_WriteByte(ONEWIRE_CMD_SKIPROM);
	DS2482_1Wire_WriteByte(DS18B20_CMD_CONVERTTEMP);

	Delay_msec(375);

	DS2482_1W_Reset();
	
	DS2482_1Wire_WriteByte(ONEWIRE_CMD_SKIPROM);
	DS2482_1Wire_WriteByte(ONEWIRE_CMD_RSCRATCHPAD);

	OWBlock(data, 2);
	
	uint16_t fpTemperature = (((uint16_t) data[1]) << 11)
	| (((uint16_t) data[0]) << 3);
	

	return (float) fpTemperature * 0.0078125;
}
////////////////////////////////////////////////////////////////////////////




/********************************* END OF FILE ********************************/
/******************************************************************************/ 

