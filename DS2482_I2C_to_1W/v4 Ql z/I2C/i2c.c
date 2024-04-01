/**
  ******************************************************************************
  * @file		i2c.c
  ******************************************************************************
  */

 
/********************/
/********///includes: 
  
	#include "i2c.h"

/********************/
/********///Functions:  

	/* Function for transmitting 8bit data via I2C */
void write_i2c(uint8_t Data)
{
	I2C_TransmitData8(I2C_Periph1, Data); 
	while(!I2C_IsActiveFlag_TXE(I2C_Periph1));
}

////////////////////////////////////////////////////////////////////////////

	/* Function for receiving 8bit data via I2C */
uint8_t read_i2c(bool IsAck)
{
	if(!IsAck)
		I2C_AcknowledgeNextData(I2C_Periph1, I2C_NACK);
	else
		I2C_AcknowledgeNextData(I2C_Periph1, I2C_ACK);
	
	uint8_t Data;
	while(!I2C_IsActiveFlag_RXNE(I2C_Periph1));
	Data = I2C_ReceiveData8(I2C_Periph1);
	return Data;
}

////////////////////////////////////////////////////////////////////////////
	/* Function for sending and confirming slave address for write and read operations
	put RW = write for write and RW = read for read operations */

bool send_i2c1_slave_address(uint8_t address, bool RW) 
{	
	address = RW ? (address | I2C_REQUEST_READ) : (address | I2C_REQUEST_WRITE);
	I2C_TransmitData8(I2C_Periph1, address);    // Set Address of the slave, Enable Write mode
	
//	uint8_t timeout = 10;
	while(!I2C_IsActiveFlag_ADDR(I2C_Periph1)) 	// Loop until ADDR flag is raised
	{
//		Delay_msec(1);
//		timeout--;
//		if(timeout<1)
//			return false;
	};
	
	I2C_ClearFlag_ADDR(I2C_Periph1);						// Clear ADDR flag value in ISR register
	
	return true;
	}
/********************************* END OF FILE ********************************/
/******************************************************************************/ 

