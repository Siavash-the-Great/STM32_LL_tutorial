/**
  ******************************************************************************
  * @file		servo.h
  ******************************************************************************
  */
 
/********************/
/********///includes: 
  
	#include <stdbool.h>
	#include "servo_config.h.h"

/********************/
/********///definitions:

	
/********************/
/********///variables:


/********************/
/********///Functions:  

	/* Function for transmitting 8bit data via I2C */
	bool servo_moveto(int degree);
	
	void servo_init(void);

/********************************* END OF FILE ********************************/
/******************************************************************************/ 

