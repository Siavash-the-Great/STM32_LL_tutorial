/**
  ******************************************************************************
  * @file		i2c.c
  ******************************************************************************
  */

 
/********************/
/********///includes: 
  
	#include "i2c.h"
/********************/
/********///definitions:

//#define X_NOP()		{__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();}
//#define Y_NOP()		X_NOP();X_NOP();X_NOP();X_NOP();X_NOP();X_NOP();X_NOP();X_NOP();X_NOP();X_NOP();
//#define Z_NOP()		Y_NOP();Y_NOP();Y_NOP();Y_NOP();Y_NOP();Y_NOP();Y_NOP();Y_NOP();Y_NOP();Y_NOP();
//#define Z2_NOP()	Z_NOP();Z_NOP();Z_NOP();Z_NOP();Z_NOP();Z_NOP();Z_NOP();Z_NOP();Z_NOP();Z_NOP();


/***********************  Commands ***********************/
	
/********************/
/********///variables:


/********************/
/********///Functions:  

	/* Function for transmitting 8bit data via I2C */
void write_i2c(uint8_t Data)
{
	LL_I2C_TransmitData8(I2C1, Data); 
	while(!LL_I2C_IsActiveFlag_TXE(I2C1));
}

////////////////////////////////////////////////////////////////////////////

	/* Function for receiving 8bit data via I2C */
uint8_t read_i2c(bool IsAck)
{
	if(!IsAck)
		LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_NACK);
	else
		LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_ACK);
	
	uint8_t Data;
	while(!LL_I2C_IsActiveFlag_RXNE(I2C1));
	Data = LL_I2C_ReceiveData8(I2C1);
	return Data;
}


/********************************* END OF FILE ********************************/
/******************************************************************************/ 

