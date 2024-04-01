/**
  ******************************************************************************
  * @file		DS18B20.h
  ******************************************************************************
  */
 
/********************/
/********///includes: 
  
	#include "onewire.h"
	#include "DS18B20Config.h"
	#include <stdbool.h>
	
/********************/
/********///definitions:

typedef struct
{
	uint8_t 	Address[8];
	float 		Temperature;
	bool		DataIsValid;	
	
}Ds18b20Sensor_t;

#define DS18B20_DECIMAL_STEPS_12BIT		0.0625
#define DS18B20_DECIMAL_STEPS_11BIT		0.125
#define DS18B20_DECIMAL_STEPS_10BIT		0.25
#define DS18B20_DECIMAL_STEPS_9BIT		0.5

/***********************  Commands ***********************/
	
/********************/
/********///variables:


/********************/
/********///Functions:  
  
	/*********************** Initialization ***********************/	


	/*********************** Card capacity details ***********************/	
	
	
/********************************* END OF FILE ********************************/
/******************************************************************************/ 

