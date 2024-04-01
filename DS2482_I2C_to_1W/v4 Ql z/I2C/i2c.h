/**
  ******************************************************************************
  * @file		i2c.h
  ******************************************************************************
  */
 
/********************/
/********///includes: 
  
	#include <stdbool.h>
	#include "stm32f1xx_ll_i2c.h"
//	#include "stm32f1xx_ll_utils.h"
/********************/
/********///definitions:

#define I2C_REQUEST_WRITE			0x00
#define I2C_REQUEST_READ			0x01
#define I2C_Slave_Adr					0x30

#define I2C_Periph1						I2C1
#define I2C_ACK								LL_I2C_ACK
#define I2C_NACK							LL_I2C_NACK

#define write 								false
#define read 									true
	
#define u8										uint8_t
#define u32										uint32_t




//#define X_NOP()		{__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();}
//#define Y_NOP()		X_NOP();X_NOP();X_NOP();X_NOP();X_NOP();X_NOP();X_NOP();X_NOP();X_NOP();X_NOP();
//#define Z_NOP()		Y_NOP();Y_NOP();Y_NOP();Y_NOP();Y_NOP();Y_NOP();Y_NOP();Y_NOP();Y_NOP();Y_NOP();
//#define Z2_NOP()	Z_NOP();Z_NOP();Z_NOP();Z_NOP();Z_NOP();Z_NOP();Z_NOP();Z_NOP();Z_NOP();Z_NOP();

/********///function definitions:

//#define Delay_msec(x)	LL_mDelay(x);	//

#define	I2C_AcknowledgeNextData(i2c, ack) 		LL_I2C_AcknowledgeNextData(i2c, ack)
#define I2C_IsActiveFlag_ADDR(i2c)						LL_I2C_IsActiveFlag_ADDR(i2c)
#define	I2C_ClearFlag_ADDR(i2c)								LL_I2C_ClearFlag_ADDR(i2c)
#define	I2C_GenerateStartCondition(i2c)				LL_I2C_GenerateStartCondition(i2c)
#define	I2C_GenerateStopCondition(i2c)				LL_I2C_GenerateStopCondition(i2c)
#define I2C_TransmitData8(i2c, data)					LL_I2C_TransmitData8(i2c, data)
#define I2C_IsActiveFlag_TXE(i2c)							LL_I2C_IsActiveFlag_TXE(i2c)
#define	I2C_IsActiveFlag_RXNE(i2c) 						LL_I2C_IsActiveFlag_RXNE(i2c)
#define	I2C_ReceiveData8(i2c)									LL_I2C_ReceiveData8(i2c)
/***********************  Commands ***********************/
	
/********************/
/********///variables:


/********************/
/********///Functions:  

	/* Function for transmitting 8bit data via I2C */
void write_i2c(uint8_t Data);

	/* Function for receiving 8bit data via I2C */
uint8_t read_i2c(bool IsAck);

	/* Function for sending and confirming slave address */
bool send_i2c1_slave_address(uint8_t address, bool RW); 

/********************************* END OF FILE ********************************/
/******************************************************************************/ 

