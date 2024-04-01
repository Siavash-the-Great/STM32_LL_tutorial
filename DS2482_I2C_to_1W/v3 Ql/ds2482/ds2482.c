/**
  ******************************************************************************
  * @file		ds2482.c
  ******************************************************************************
  */

 
/********************/
/********///includes: 

  #include "ds2482.h"

/********************/
/********///Functions:  

//--------------------------------------------------------------------------
// DS2482 Initialization function
bool DS2482_Initialize(void)
{
	u8 inst_buf[2] = {Device_Reset, One_Wire_Reset};
	Ql_IIC_Write(0, I2C_Slave_Adr, inst_buf, 2);

	return true;
}


//--------------------------------------------------------------------------
//function to reset the OneWire bus
bool DS2482_1W_Reset(void)
{
	u8 inst_buf[1] = {One_Wire_Reset};
 	Ql_IIC_Write(0, I2C_Slave_Adr, inst_buf, 1);
	
	return true;
}

//--------------------------------------------------------------------------
		/* Function for writing 8bit data to the 1-wire slave */
bool DS2482_1Wire_WriteByte(uint8_t data)
{
	u8 inst_buf[2] = {One_Wire_Write_Byte, data};
	Ql_IIC_Write(0, I2C_Slave_Adr, inst_buf, 2);
	
	return true;
}

//--------------------------------------------------------------------------
		/* Function for reading 8bit data from the 1-wire slave */
uint8_t DS2482_1Wire_ReadByte(void)
{
	u8 inst_buf[1] = {One_Wire_Read_Byte};
	Ql_IIC_Write(0, I2C_Slave_Adr, inst_buf, 1);
 
 	u8 inst_buf2[2] = {Set_Read_Pointer, Read_Data_Register};
	Ql_IIC_Write(0, I2C_Slave_Adr, inst_buf2, 2);

	u8 data;
	Ql_IIC_Read(0, I2C_Slave_Adr, &data, 1);
		
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

