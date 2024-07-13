/***********************************************************************************/
/***********************************************************************************/
/* Auther : Ahmed Samir */
/* Version: V0          */
/* Date   : 6/10/2022   */
/***********************************************************************************/
/***********************************************************************************/

#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H

/* Buses Names */
#define RCC_AHB                      0
#define RCC_APB1                     1
#define RCC_APB2                     2

/* Clock Systems */
#define RCC_HSI          0b00
#define RCC_HSE          0b01
#define RCC_PLL          0b10


/* Peripherals Names */
typedef enum
{
	DMA1,
	DMA2,
	SRAM,
	FLITF=4,
	CRC=6,
	FSMC=8,
	SDIO=10,
	AFIO=0,
	GPIOA=2,
	GPIOB,
	GPIOC,
	GPIOD,
	GPIOE,
	GPIOF,
	GPIOG,
	ADC1,
	ADC2,
	TIM1,
	SPI1,
	TIM8,
	USART_1,
	ADC3,
	TIM9=19,
	TIM10,
	TIM11,
	TIM2=0,
	TIM_3,
	TIM4,
	TIM5,
	TIM6,
	TIM7,
	TIM12,
	TIM13,
	TIM14,
	WWDG=11,
	SPI2=14,
	SPI3,
	USART_2=17,
	USART_3,
	UART_4,
	UART_5,
	I2C1,
	I2C2,
	USB,
	CAN1=25,
	BKP=27,
	PWR,
	DAC

}peripherals_t;


/* Prototypes of functions */
void MRCC_voidInit(void);
void MRCC_voidPeripheralClockEnable(u8 Copy_u8BusName,peripherals_t Copy_u8PeripheralName);
void MRCC_voidPeripheralClockDisable(u8 Copy_u8BusName,peripherals_t Copy_u8PeripheralName);

#endif
