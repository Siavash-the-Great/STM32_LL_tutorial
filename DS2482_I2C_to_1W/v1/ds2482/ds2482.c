/**
  ******************************************************************************
  * @file		ds2482.c
  ******************************************************************************
  */

 
/********************/
/********///includes: 
  
	#include "ds2482.h"
/********************/
/********///definitions:


/********************/
/********///variables:


/********************/
/********///Functions:  

//--------------------------------------------------------------------------
// DS2482 Initialization function
bool DS2482_Initialize(void)
{
 	LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_ACK);
	
	LL_I2C_GenerateStartCondition(I2C1);

		Delay_msec(1);
	
	LL_I2C_TransmitData8(I2C1, I2C_Slave_Adr | I2C_REQUEST_WRITE);    	// Set Address of the slave, Enable Write mode
	while(!LL_I2C_IsActiveFlag_ADDR(I2C1)) {}; 							// Loop until ADDR flag is raised
	LL_I2C_ClearFlag_ADDR(I2C1);
	
	write_i2c(Device_Reset);
		
 	LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_ACK);
	
	write_i2c(One_Wire_Reset);
	
	LL_I2C_GenerateStopCondition(I2C1);	 
	
	return true;
}


//--------------------------------------------------------------------------
//function to reset the OneWire bus
bool DS2482_1W_Reset(void)
{
 	LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_ACK);
	
	LL_I2C_GenerateStartCondition(I2C1);

		Delay_msec(1);	
	LL_I2C_TransmitData8(I2C1, I2C_Slave_Adr | I2C_REQUEST_WRITE);    	// Set Address of the slave, Enable Write mode
	while(!LL_I2C_IsActiveFlag_ADDR(I2C1)) {}; 							// Loop until ADDR flag is raised
	LL_I2C_ClearFlag_ADDR(I2C1);
	
	write_i2c(One_Wire_Reset);
	
	LL_I2C_GenerateStopCondition(I2C1);	 
	
	return true;
}




//--------------------------------------------------------------------------
		/* Function for writing 8bit data to the 1-wire slave */
bool DS2482_1Wire_WriteByte(uint8_t data)
{
	LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_ACK);
	
	LL_I2C_GenerateStartCondition(I2C1);

		Delay_msec(1);
	
	LL_I2C_TransmitData8(I2C1, I2C_Slave_Adr | I2C_REQUEST_WRITE);    	// Set Address of the slave, Enable Write mode
	while(!LL_I2C_IsActiveFlag_ADDR(I2C1)) {}; 							// Loop until ADDR flag is raised
	LL_I2C_ClearFlag_ADDR(I2C1);										// Clear ADDR flag value in ISR register

	write_i2c(One_Wire_Write_Byte);
	write_i2c(data);
	
	LL_I2C_GenerateStopCondition(I2C1);
		
	return true;
}

//--------------------------------------------------------------------------
		/* Function for reading 8bit data from the 1-wire slave */
uint8_t DS2482_1Wire_ReadByte(void)
{
	LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_ACK);
	
	LL_I2C_GenerateStartCondition(I2C1);

		Delay_msec(1);	
	
	LL_I2C_TransmitData8(I2C1, I2C_Slave_Adr | I2C_REQUEST_WRITE);    	// Set Address of the slave, Enable Write mode
	while(!LL_I2C_IsActiveFlag_ADDR(I2C1)) {}; 							// Loop until ADDR flag is raised
	LL_I2C_ClearFlag_ADDR(I2C1);										// Clear ADDR flag value in ISR register
		
	write_i2c(One_Wire_Read_Byte);
	write_i2c(One_Wire_Read_Byte);		
		
	LL_I2C_GenerateStopCondition(I2C1);

	LL_I2C_GenerateStartCondition(I2C1);
	
		Delay_msec(1);

	LL_I2C_TransmitData8(I2C1, I2C_Slave_Adr | I2C_REQUEST_WRITE);    	// Set Address of the slave, Enable Write mode
	while(!LL_I2C_IsActiveFlag_ADDR(I2C1)) {}; 							// Loop until ADDR flag is raised
	LL_I2C_ClearFlag_ADDR(I2C1);										// Clear ADDR flag value in ISR register
		
	write_i2c(Set_Read_Pointer);
	write_i2c(Read_Data_Register);
	
	LL_I2C_GenerateStartCondition(I2C1);

		Delay_msec(1);	
		
	LL_I2C_TransmitData8(I2C1, I2C_Slave_Adr | I2C_REQUEST_READ);    	// Set Address of the slave, Enable Write mode
	while(!LL_I2C_IsActiveFlag_ADDR(I2C1)) {}; 							// Loop until ADDR flag is raised
	LL_I2C_ClearFlag_ADDR(I2C1);										// Clear ADDR flag value in ISR register

	LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_NACK);

	uint8_t data = read_i2c(false);

	LL_I2C_GenerateStopCondition(I2C1);
		
	return data;
}

//--------------------------------------------------------------------------
		/* Function for reading 16bit data from the 1-wire slave */
uint16_t DS2482_1Wire_Read2Byte(void)
{
	LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_ACK);
	
	LL_I2C_GenerateStartCondition(I2C1);

		Delay_msec(1);	
	
	LL_I2C_TransmitData8(I2C1, I2C_Slave_Adr | I2C_REQUEST_WRITE);    	// Set Address of the slave, Enable Write mode
	while(!LL_I2C_IsActiveFlag_ADDR(I2C1)) {}; 							// Loop until ADDR flag is raised
	LL_I2C_ClearFlag_ADDR(I2C1);										// Clear ADDR flag value in ISR register

	write_i2c(One_Wire_Read_Byte);

	LL_I2C_GenerateStopCondition(I2C1);

	LL_I2C_GenerateStartCondition(I2C1);
		
		Delay_msec(1);	//

	LL_I2C_TransmitData8(I2C1, I2C_Slave_Adr | I2C_REQUEST_WRITE);    	// Set Address of the slave, Enable Write mode
	while(!LL_I2C_IsActiveFlag_ADDR(I2C1)) {}; 							// Loop until ADDR flag is raised
	LL_I2C_ClearFlag_ADDR(I2C1);										// Clear ADDR flag value in ISR register
		
	write_i2c(Set_Read_Pointer);
	write_i2c(Read_Data_Register);
	
	LL_I2C_GenerateStartCondition(I2C1);
	
		Delay_msec(1);	//	
		
	LL_I2C_TransmitData8(I2C1, I2C_Slave_Adr | I2C_REQUEST_READ);    	// Set Address of the slave, Enable Write mode
	while(!LL_I2C_IsActiveFlag_ADDR(I2C1)) {}; 							// Loop until ADDR flag is raised
	LL_I2C_ClearFlag_ADDR(I2C1);										// Clear ADDR flag value in ISR register
		
		uint16_t data = read_i2c(true) << 8;

	LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_NACK);

		data = read_i2c(false) | data;
		
	LL_I2C_GenerateStopCondition(I2C1);
		
	return data;
}

//--------------------------------------------------------------------------
// Send 8 bits of communication to the 1-Wire Net and return the
// result 8 bits read from the 1-Wire Net. The parameter 'sendbyte'
// least significant 8 bits are used and the least significant 8 bits
// of the result are the return byte.
//
// 'sendbyte' - 8 bits to send (least significant byte)
//
// Returns:  8 bits read from sendbyte
//
unsigned char OWTouchByte(unsigned char sendbyte)
{
   if (sendbyte == 0xFF)
      return DS2482_1Wire_ReadByte();	
   else
   
{
      DS2482_1Wire_WriteByte(sendbyte);	
      return sendbyte;
   }
}

//--------------------------------------------------------------------------
// The 'OWBlock' transfers a block of data to and from the
// 1-Wire Net. The result is returned in the same buffer.
//
// 'tran_buf' - pointer to a block of unsigned
//              chars of length 'tran_len' that will be sent
//              to the 1-Wire Net
// 'tran_len' - length in bytes to transfer
//
void OWBlock(unsigned char *tran_buf, int tran_len)
{
   int i;

   for (i = 0; i < tran_len; i++)
      tran_buf[i] = OWTouchByte(tran_buf[i]);
}

////////////////////////////////////////////////////////////////////////////




/********************************* END OF FILE ********************************/
/******************************************************************************/ 

