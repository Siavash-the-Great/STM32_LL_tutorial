/**
  ******************************************************************************
  * @file		servo_config.h
  ******************************************************************************
  */
 
/********************/
/********///includes: 
  
	#include "stm32f1xx_ll_utils.h"
	#include "stm32f1xx_ll_tim.h"
/********************/
/********///definitions:
//servo's angle range in Degrees
#define Angle_Range 				180
// Minimum pulse width in microsecends that corresponds to servo's 0 degree postion
#define Min_Pulse_Width 		550		
// Maxmum pulse width in microsecends that corresponds to servo's 180 degree postion
#define Max_Pulse_Width 		2800	
// Range of pulse width in microsecends that corresponds to servo's angle range
#define Pulse_Width_Range 	(Max_Pulse_Width -  Min_Pulse_Width)
//Appropriate PWM wave period in microsecends
#define PWM_period					20000								true
	

/********///function definitions:

#define Delay_msec(x)	LL_mDelay(x);


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

