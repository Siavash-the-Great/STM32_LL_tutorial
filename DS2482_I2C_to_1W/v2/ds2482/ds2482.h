/**
  ******************************************************************************
  * @file		ds2482.h
  ******************************************************************************
  */

 
/********************/
/********///includes: 
  
	#include "i2c.h"
/********************/
/********///definitions:	
/***********************  Commands ***********************/
#define Device_Reset			0xF0
#define Set_Read_Pointer		0xE1
#define Write_Configuration		0xD2
#define One_Wire_Reset			0xB4
#define One_Wire_Single_Bit		0x87
#define One_Wire_Write_Byte		0xA5
#define One_Wire_Read_Byte		0x96
#define One_Wire_Triplet		0x78	

/*****************  address of registers *****************/
#define Status_Register			0xF0
#define Read_Data_Register		0xE1
#define Configuration_Register	0xC3	
	
/********************/
/********///variables:


/********************/
/********///Functions:  

bool DS2482_Initialize(void);
bool DS2482_1W_Reset(void);
bool DS2482_1Wire_WriteByte(uint8_t data);
uint8_t DS2482_1Wire_ReadByte(void);
uint16_t DS2482_1Wire_Read2Byte(void);
unsigned char OWTouchByte(unsigned char sendbyte);
void OWBlock(unsigned char *tran_buf, int tran_len);
	
////////////////////////////////////////////////////////////////////////////




/********************************* END OF FILE ********************************/
/******************************************************************************/ 

