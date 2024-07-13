/***********************************************************************************************/
/***********************************************************************************************/
/************************************* Author: Ahmed Samir *************************************/
/***************************************** Layer: MCAL *****************************************/
/***************************************** SWC: USART  *****************************************/
/***************************************** Version: 1.0 ****************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#ifndef USART_INTERFACE_H
#define USART_INTERFACE_H

/* peripherals options */
#define UART1               1
#define UART2               2
#define UART3               3

/* Massages types */
#define UART_CHAR                 1
#define UART_INT                  2
#define UART_FLOAT                3
#define UART_STRING               4

/* Prototypes of functions */
void MUSART_voidInitialization(u8 Copy_u8Uart);
void MUSART_voidTransmitArr(u8 Copy_u8Uart , u8 Copy_Arr[]);
void MUSART_voidTransmitChar(u8 Copy_u8Uart , u8 Copy_u8Char);
u8 MUSART_u8Receive(void);
void USART_voidmsgint(u8 Copy_u8Uart,s32 msg);
u8 MUSART_u8Receive_Interrupt(u8 Copy_u8Uart);
//void MUSART_voidTransmitINT(u8 Copy_u8Uart , u8 Copy_u8Data);


#endif
