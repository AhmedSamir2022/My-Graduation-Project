/***********************************************************************************************/
/***********************************************************************************************/
/************************************* Author: Ahmed Samir *************************************/
/***************************************** Layer: MCAL *****************************************/
/***************************************** SWC: USART  *****************************************/
/***************************************** Version: 1.0 ****************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "USART_interface.h"
#include "USART_config.h"
#include "USART_private.h"

#include "RCC_INTERFACE.h"
#include "GPIO_interface.h"


#include <stdio.h>
#include <math.h>
#include <string.h>

void (*USART_CallBack)(void);

void MUSART_voidInitialization(u8 Copy_u8Uart)
{
	switch(Copy_u8Uart)
	{
	case UART1:
		MRCC_voidPeripheralClockEnable(RCC_APB1,USART_1);
		/* UART1 pins configurations */
		/* PA9 in AF output mode for UART */
		MGPIO_voidSetPinMode(PORTA,PIN9,GPIO_AF_OUTPUT_PP_50MHZ);
		/* PA10 in input floating mode for UART */
		MGPIO_voidSetPinMode(PORTA,PIN10,GPIO_INPUT_FLOATING);
		/* select the baud rate */
		USART1->BRR =UART_BAUDRATE;
		/* enable TX */
		SET_BIT(USART1->CR1,2);
		/* enable RX */
		SET_BIT(USART1->CR1,3);
		/* enable UART */
		SET_BIT(USART1->CR1,13);

		/* TXNE interrupt enable */
		SET_BIT(USART1->CR1,7);
		/* RXNE interrupt enable */
		SET_BIT(USART1->CR1,5);

		/* Clear Status Register */
		USART1->SR = 0;
		break;
	case UART2:
		MRCC_voidPeripheralClockEnable(RCC_APB1,USART_2);
		/* UART2 pins configurations */
		/* PB10 in AF output mode for UART */
		MGPIO_voidSetPinMode(PORTA,PIN2,GPIO_AF_OUTPUT_PP_50MHZ);
		/* PB11 in input floating mode for UART */
		MGPIO_voidSetPinMode(PORTA,PIN3,GPIO_INPUT_FLOATING);
		/* select the baud rate */
		USART2->BRR =UART_BAUDRATE;
		/* enable TX */
		SET_BIT(USART2->CR1,2);
		/* enable RX */
		SET_BIT(USART2->CR1,3);
		/* enable UART */
		SET_BIT(USART2->CR1,13);

		/* TXNE interrupt enable */
		SET_BIT(USART2->CR1,7);
		/* RXNE interrupt enable */
		SET_BIT(USART2->CR1,5);

		/* Clear Status Register */
		USART2->SR = 0;
		break;
	case UART3:
		MRCC_voidPeripheralClockEnable(RCC_APB1,USART_3);

			/* UART3 pins configurations */
			/* PB10 in AF output mode for UART */
			MGPIO_voidSetPinMode(PORTB,PIN10,GPIO_AF_OUTPUT_PP_50MHZ);
			/* PB11 in input floating mode for UART */
			MGPIO_voidSetPinMode(PORTB,PIN11,GPIO_INPUT_FLOATING);
		/* select the baud rate */
		USART3->BRR =UART_BAUDRATE;
		/* enable TX */
		SET_BIT(USART3->CR1,2);
		/* enable RX */
		SET_BIT(USART3->CR1,3);
		/* enable UART */
		SET_BIT(USART3->CR1,13);

		/* TXNE interrupt enable */
		SET_BIT(USART3->CR1,7);
		/* RXNEIE interrupt enable */
		SET_BIT(USART3->CR1,5);

		/* Clear Status Register */
		USART3->SR = 0;
		break;

	}

}

//void MUSART_voidTransmitINT(u8 Copy_u8Uart , u8 Copy_u8Data)
//{
//	char array[16];
//	u32 Local_u32TimeOut = 0;
//
//	sprintf(array, "%d", *(int *)Copy_u8Data);
//
//	for(int i=0;(array[i]!='\0');i++)
//	{
//		while((USART3->SR&(1<<7)) == 0  && Local_u32TimeOut<100000){Local_u32TimeOut++;} //wait until the TXE flag is set
//		USART3->DR = array[i];
//		Local_u32TimeOut=0;
//		while((USART3->SR&(1<<6)) == 0  && Local_u32TimeOut<100000){Local_u32TimeOut++;} //wait until the TC flag is set
//		USART3->SR &= ~(1<<6);
//	}
//
//}

void USART_voidmsgint(u8 Copy_u8Uart,s32 msg)
{
		char buffer[2000];
		itoa(msg,buffer,10);
		u8*pmsg=(u8*)buffer;
		u8 LOC_u8Iterator = 0;
	switch(Copy_u8Uart)
	{
	case UART1:
		while(pmsg[LOC_u8Iterator] != '\0')
			{
				USART1->DR = pmsg[LOC_u8Iterator];
				while( GET_BIT(USART1->SR,6) == 0);
				CLR_BIT(USART1->SR,6);
				LOC_u8Iterator++;
			}
		break;
	case UART2:
		while(pmsg[LOC_u8Iterator] != '\0')
			{
				USART2->DR = pmsg[LOC_u8Iterator];
				while( GET_BIT(USART2->SR,6) == 0);
				CLR_BIT(USART2->SR,6);
				LOC_u8Iterator++;
			}
		break;
	case UART3:
		while(pmsg[LOC_u8Iterator] != '\0')
			{
				USART3->DR = pmsg[LOC_u8Iterator];
				while( GET_BIT(USART3->SR,6) == 0);
				CLR_BIT(USART3->SR,6);
				LOC_u8Iterator++;
			}
		break;
	default:
		break;
		// error
	}


}


void MUSART_voidTransmitArr(u8 Copy_u8Uart , u8 Copy_Arr[])
{
	u32 Local_u32TimeOut = 0;

	switch(Copy_u8Uart)
	{
	case UART1:
		for(int i=0;*(u8*)(Copy_Arr+i)!='\0';i++)
		{
			while((USART1->SR&(1<<7)) == 0 && Local_u32TimeOut<100000) //wait until the TXE flag is set
			{
				Local_u32TimeOut++;
			}
			USART1->DR = *(u8*)(Copy_Arr+i);
			Local_u32TimeOut=0;
			while((USART1->SR&(1<<6)) == 0 && Local_u32TimeOut<100000) //wait until the TC flag is set
			{
				Local_u32TimeOut++;
			}
			USART1->SR &= ~(1<<6);
		}
		break;
	case UART2:
		for(int i=0;*(u8*)(Copy_Arr+i)!='\0';i++)
		{
			while((USART2->SR&(1<<7)) == 0 && Local_u32TimeOut<100000) //wait until the TXE flag is set
			{
				Local_u32TimeOut++;
			}
			USART2->DR = *(u8*)(Copy_Arr+i);
			Local_u32TimeOut=0;
			while((USART2->SR&(1<<6)) == 0 && Local_u32TimeOut<100000) //wait until the TC flag is set
			{
				Local_u32TimeOut++;
			}
			USART2->SR &= ~(1<<6);
		}
		break;
	case UART3:
		for(int i=0;*(u8*)(Copy_Arr+i)!='\0';i++)
		{
			while((USART3->SR&(1<<7)) == 0 && Local_u32TimeOut<100000) //wait until the TXE flag is set
			{
				Local_u32TimeOut++;
			}
			USART3->DR = *(u8*)(Copy_Arr+i);
			Local_u32TimeOut=0;
			while((USART3->SR&(1<<6)) == 0 && Local_u32TimeOut<100000) //wait until the TC flag is set
			{
				Local_u32TimeOut++;
			}
			USART3->SR &= ~(1<<6);
		}
		break;
	}

}

void MUSART_voidTransmitChar(u8 Copy_u8Uart , u8 Copy_u8Char)
{
	switch(Copy_u8Uart)
	{
	case UART1:
		USART1->DR = Copy_u8Char;
		/* Wait till transmission complete */
		while(((USART1->SR >> 6)&1) == 0);
		/* Clear TC bit */
		USART1->SR &= ~(0b1 << 6);
		break;
	case UART2:
		USART2->DR = Copy_u8Char;
		/* Wait till transmission complete */
		while(((USART2->SR >> 6)&1) == 0);
		/* Clear TC bit */
		USART2->SR &= ~(0b1 << 6);
		break;
	case UART3:
		USART3->DR = Copy_u8Char;
		/* Wait till transmission complete */
		while(((USART3->SR >> 6)&1) == 0);
		/* Clear TC bit */
		USART3->SR &= ~(0b1 << 6);
		break;
	}

}

u8 MUSART_u8Receive(void)
{
//	switch(Copy_u8Uart)
//	{
//	case UART1:
//		/* Wait till Receive complete */
//		while(((USART1->SR >> 5)&1) == 0);
//		return (0xFF & USART1->DR);
//		break;
//	case UART2:
//		/* Wait till Receive complete */
//		while(((USART2->SR >> 5)&1) == 0);
//
//		return (0xFF & USART2->DR);
//		break;
//	case UART3:
		/* Wait till Receive complete */
		while(((USART3->SR >> 5)&1) == 0);

		return (0xFF & USART3->DR);
//		break;
//	}
}

/* ISR */
void USART3_IRQHandler(void)
{
	USART_CallBack();
}

