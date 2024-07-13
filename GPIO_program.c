/***********************************************************************************/
/***********************************************************************************/
/* Auther : Ahmed Samir */
/* Version: V0          */
/* Date   : 6/10/2022   */
/***********************************************************************************/
/***********************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "GPIO_config.h"
#include "GPIO_private.h"

void MGPIO_voidSetPinMode(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8Mode)
{
	switch(Copy_u8Port)
	{
	case PORTA:
		if(Copy_u8Pin <= 7)
		{
			GPIOA->CRL &= ~((0b1111) << (Copy_u8Pin * 4));
			GPIOA->CRL |= (Copy_u8Mode << (Copy_u8Pin * 4));
		}
		else if(Copy_u8Pin <= 15)
		{
			Copy_u8Pin = Copy_u8Pin - 8;
			GPIOA->CRH &= ~((0b1111) << (Copy_u8Pin * 4));
			GPIOA->CRH |= (Copy_u8Mode << (Copy_u8Pin * 4));
		}
		break;

	case PORTB:
		if(Copy_u8Pin <= 7)
		{
			GPIOB->CRL &= ~((0b1111) << ((Copy_u8Pin) * 4));
			GPIOB->CRL |= (Copy_u8Mode << ((Copy_u8Pin) * 4));
		}
		else if(Copy_u8Pin <= 15)
		{
			Copy_u8Pin = Copy_u8Pin - 8;
			GPIOB->CRH &= ~((0b1111) << (Copy_u8Pin * 4));
			GPIOB->CRH |= (Copy_u8Mode << (Copy_u8Pin * 4));
		}
		break;

	case PORTC:
		if(Copy_u8Pin <= 7)
		{
			GPIOC->CRL &= ~((0b1111) << (Copy_u8Pin * 4));
			GPIOC->CRL |= (Copy_u8Mode << (Copy_u8Pin * 4));
		}
		else if(Copy_u8Pin <= 15)
		{
			Copy_u8Pin = Copy_u8Pin - 8;
			GPIOC->CRH &= ~((0b1111) << (Copy_u8Pin * 4));
			GPIOC->CRH |= (Copy_u8Mode << (Copy_u8Pin * 4));
		}
		break;
	}
}

void MGPIO_voidSetPinValue(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8Value)
{
	switch(Copy_u8Port)
	{
	case PORTA:
		if(Copy_u8Value == GPIO_HIGH)
			GPIOA->BSRR = (1 << Copy_u8Pin);
		else if(Copy_u8Value == GPIO_LOW)
			GPIOA->BRR = (1 << Copy_u8Pin);
	    break;

	case PORTB:
		if(Copy_u8Value == GPIO_HIGH)
			GPIOB->BSRR = (1 << Copy_u8Pin);
		else if(Copy_u8Value == GPIO_LOW)
			GPIOB->BRR = (1 << Copy_u8Pin);
	    break;

	case PORTC:
		if(Copy_u8Value == GPIO_HIGH)
			GPIOC->BSRR = (1 << Copy_u8Pin);
		else if(Copy_u8Value == GPIO_LOW)
			GPIOC->BRR = (1 << Copy_u8Pin);
	    break;
	}
}

u8 MGPIO_u8GetPinValue(u8 Copy_u8Port,u8 Copy_u8Pin)
{
	u8 Local_u8ReturnValue = 0;

	switch(Copy_u8Port)
	{
	case PORTA:
		Local_u8ReturnValue = ((GPIOA->IDR >> Copy_u8Pin) & 1);
		break;

	case PORTB:
		Local_u8ReturnValue = ((GPIOB->IDR >> Copy_u8Pin) & 1);
		break;

	case PORTC:
		Local_u8ReturnValue = ((GPIOC->IDR >> Copy_u8Pin) & 1);
		break;
	}

	return Local_u8ReturnValue;
}

void MGPIO_voidSetPortValue(u8 Copy_u8Port,u16 Copy_u16Value)
{
	switch(Copy_u8Port)
	{
	case PORTA:
		GPIOA->ODR = Copy_u16Value;
		break;

	case PORTB:
		GPIOB->ODR = Copy_u16Value;
		break;

	case PORTC:
		GPIOC->ODR = Copy_u16Value;
		break;
	}
}
u16 MGPIO_u16GetPortValue(u8 Copy_u8Port)
{
	u16 Local_u16ReturnValue = 0;

	switch(Copy_u8Port)
	{
	case PORTA:
		Local_u16ReturnValue = GPIOA->IDR;
		break;

	case PORTB:
		Local_u16ReturnValue = GPIOB->IDR;
		break;

	case PORTC:
		Local_u16ReturnValue = GPIOC->IDR;
		break;
	}

	return Local_u16ReturnValue;

}
