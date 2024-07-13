/*
 * EXTI_program.c
 *
 *  Created on: Aug 9, 2022
 *      Author: moham
 */


#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_config.h"


/* define Callback Global variable (pointer to function) */
static void (*EXTI_CallBack[16]) (void);

/*
 * Configures the trigger signal EXTI for a certain line
 */
void EXTI_voidSelectTrig(u8 Copy_u8EXTI_line, u8 Copy_u8Selection){
	switch(Copy_u8Selection){
	case EXTI_RISING_TRIGGER:
		SET_BIT(EXTI->RTSR, Copy_u8EXTI_line);
		CLR_BIT(EXTI->FTSR, Copy_u8EXTI_line);
	break;
	case EXTI_FALLING_TRIGGER:
		CLR_BIT(EXTI->RTSR, Copy_u8EXTI_line);
		SET_BIT(EXTI->FTSR, Copy_u8EXTI_line);
	break;
	case EXTI_BOTH_TRIGGER:
		SET_BIT(EXTI->RTSR, Copy_u8EXTI_line);
		SET_BIT(EXTI->FTSR, Copy_u8EXTI_line);
	break;
	}
}

/*
 * Configures the trigger signal EXTI for a certain line
 */
void EXTI_voidControlLine(u8 Copy_u8EXTI_line, u8 Copy_u8State){

	switch(Copy_u8State){

	case EXTI_ENABLE:
		SET_BIT(EXTI->IMR, Copy_u8EXTI_line);
		break;
	case EXTI_DISABLE:
		CLR_BIT(EXTI->IMR, Copy_u8EXTI_line);
		break;
	}
}

/*
 * Clearing the xPIF for EXTI for a certain line
 */
void EXTI_voidClearFlag(u8 Copy_u8EXTI_line){
		SET_BIT(EXTI->PR, Copy_u8EXTI_line);
}

/*************	 Function OF Set CallBack  **********************/

void EXTI_voidSetCallBack (u8 Copy_u8EXTILine,void (*ptr) (void))
{
	EXTI_CallBack[Copy_u8EXTILine] = ptr;
}





/*************	 Function OF EXTIx_ISQHandler Interrupt  **************************/
/* This is function call a EXTI_CallBack() function to do when interrupt */

void EXTI0_IRQHandler (void)
{
	EXTI_CallBack[0]();
	/*	Clear pending Bit		*/
	SET_BIT(EXTI->PR , 0);

}
void EXTI1_IRQHandler (void)
{
	EXTI_CallBack[1]();
	/*	Clear pending Bit		*/
	SET_BIT(EXTI->PR , 1);

}
void EXTI2_IRQHandler (void)
{
	EXTI_CallBack[2]();
	/*	Clear pending Bit		*/
	SET_BIT(EXTI->PR , 2);

}
void EXTI3_IRQHandler (void)
{
	EXTI_CallBack[3]();
	/*	Clear pending Bit		*/
	SET_BIT(EXTI->PR , 3);

}
void EXTI4_IRQHandler (void)
{
	EXTI_CallBack[4]();
	/*	Clear pending Bit		*/
	SET_BIT(EXTI->PR , 4);

}
void EXTI9_5_IRQHandler (void)
{
	u8 get=0;
	for(u8 j=5; j<=9; j++)
	{
		get = GET_BIT(EXTI->PR,j);
		if(get == 1)
		{
			EXTI_CallBack[j]();
		}
		get=0;
	}
	EXTI->PR |= 0x03E0; /* clear interrupt pending flag 5~9 */

}
void EXTI15_10_IRQHandler (void)
{
	u8 get=0;
		for(u8 j=10; j<=15; j++)
		{
			get = GET_BIT(EXTI->PR,j);
			if(get == 1)
			{
				EXTI_CallBack[j]();

			}
			get=0;
		}
	EXTI->PR |= 0xFC00; /* clear interrupt pending flag 10~15 */

}
