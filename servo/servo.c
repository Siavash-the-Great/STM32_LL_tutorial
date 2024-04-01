/**
  ******************************************************************************
  * @file		servo.c
  ******************************************************************************
  */
 
/********************/
/********///includes: 
  
	#include "servo.h"

/********************/
/********///definitions:


/********************/
/********///variables:


/********************/
/********///Functions:  
	
	/* Function for initializing servo */
		void servo_init(void)
		{
			LL_TIM_EnableCounter(TIM1);																								//Enable Timer1's counter
			LL_TIM_CC_EnableChannel(TIM1, LL_TIM_CHANNEL_CH1);												//Enable channel1 of Timer1(PWM)
			LL_TIM_EnableAllOutputs(TIM1);																						//Enable Timer1's outputs
		}
	
	/* Function for moving servo to desired position */
		bool servo_moveto(int degree)
		{
			if((0 > degree) || (Angle_Range < degree))
			{
				return false;
			}
			
			uint32_t ARR = LL_TIM_GetAutoReload(TIM1) + 1;
			uint32_t CRR = (((((float) degree / Angle_Range) * Pulse_Width_Range) + Min_Pulse_Width) / PWM_period) * ARR;
			LL_TIM_OC_SetCompareCH1(TIM1, CRR);	//Set Duty cycle 
			return true;
		}

/********************************* END OF FILE ********************************/
/******************************************************************************/ 



/********************************* END OF FILE ********************************/
/******************************************************************************/ 

