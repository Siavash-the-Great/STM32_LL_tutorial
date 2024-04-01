/**
  ******************************************************************************
  * @file		DS18B20Config.h
  ******************************************************************************
  */
  
 //	config one timer to have a 1us clock	(for cpu clock = 72 MHz  >>> Prescaler=(72-1) , counter period=Max)
//**************************************************************************************************************//
  

/********************/
/********///definitions:
#ifndef	_DS18B20CONFIG_H
#define	_DS18B20CONFIG_H

///////////Config:
#define	_DS18B20_GPIO		GPIOA
#define	_DS18B20_PIN		LL_GPIO_PIN_8

#define	_DS18B20_USE_FREERTOS		    				0
#define _DS18B20_MAX_SENSORS		    				1
#define	_DS18B20_CONVERT_TIMEOUT_MS					5000		
#if (_DS18B20_USE_FREERTOS==1)
#define	_DS18B20_UPDATE_INTERVAL_MS					10000					//  (((	if==0  >> Ds18b20_ManualConvert()  )))    ((( if>0  >>>> Auto refresh ))) 
#endif	

#define	_DS18B20_TIMER								TIM1

#endif
/********************************* END OF FILE ********************************/
/******************************************************************************/ 

