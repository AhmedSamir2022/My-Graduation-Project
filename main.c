
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_INTERFACE.h"
#include "GPIO_interface.h"
#include "USART_interface.h"
#include "NVIC_interface.h"
#include "STK_interface.h"
#include "TIMER_interface.h"
#include "config.h"
#include "Encoder.h"
#include "PID.h"
#include "CAN_interface.h"
PID_str pid1;
PID_str pid2;
u32 DATA = 0;


/**********************************************************CAN Functions ******************************************************/
void CAN_TX(u32 Copy_Data)
{
	CAN_TxHeaderTypeDef tx_header1;
	tx_header1.StdId = 0x643;
	tx_header1.IDE = CAN_ID_STD;
	tx_header1.RTR = CAN_RTR_DATA;
	tx_header1.DLC = 4;

	CAN_voidAddTxMsgInt(&tx_header1,Copy_Data);
	//CAN_voidAddTxMsg(&tx_header1,DATA2);
	MUSART_voidTransmitArr(UART3,(u8*)"i'm master\r\n");
}

void CAN_RX(void)
{
	CAN_RxHeaderTypeDef Rx_header;
	while(CAN_voidRXPending(CAN_RX_FIFO0) == 0);
	CAN_voidGetRxMsgInt(CAN_RX_FIFO0,&Rx_header,&DATA);
	//	USART_voidmsgint(UART3,DATA);
}

u16 Std_id_High(u16 local_u16Std_Id)
{
	return (local_u16Std_Id << 5);
}

void CAN_FilterConfig(void)
{
	CAN_FilterTypeDef CAN_FilterInit;
	CAN_FilterInit.FilterActivation = ENABLE;
	CAN_FilterInit.FilterBank = 0;
	CAN_FilterInit.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	CAN_FilterInit.FilterIdHigh = Std_id_High(0x000);
	CAN_FilterInit.FilterIdLow = 0x0000;
	CAN_FilterInit.FilterMaskIdHigh = 0x0000;
	CAN_FilterInit.FilterMaskIdLow = 0x0000;
	CAN_FilterInit.FilterMode = CAN_FILTERMODE_IDMASK;
	CAN_FilterInit.FilterScale = CAN_FILTERSCALE_32BIT;

	CAN_voidConfigFilter(&CAN_FilterInit);
}

void CAN_Interrupt(void)
{
	MNVIC_EnableInterrupt(CAN_TX_IRQn);
	MNVIC_SetPendingFlag(CAN_TX_IRQn);

	MNVIC_EnableInterrupt(CAN_RX0_IRQn);
	MNVIC_SetPendingFlag(CAN_RX0_IRQn);

	MNVIC_EnableInterrupt(CAN_RX1_IRQn);
	MNVIC_SetPendingFlag(CAN_RX1_IRQn);

	MNVIC_EnableInterrupt(CAN_SCE_IRQn);
	MNVIC_SetPendingFlag(CAN_SCE_IRQn);

	CAN_voidEnableInterrupt(CAN_IER_TX_MAILBOX_EMPTY | CAN_IER_RX_FIFO0_MSG_PENDING | CAN_IER_ERROR | CAN_IER_LAST_ERROR_CODE | CAN_IER_BUSOFF);
}

void CAN_TxMailbox0CompleteCallback()
{
	/* print MSG on UART1 */
	char MSG[50] = " MSG TRANSMITED m0 \r\n";
	MUSART_voidTransmitArr(UART3,(u8*)MSG);
}
void CAN_RxFifo0MsgPendingCallback()
{
	CAN_RX();
}
void CAN_ErrorCallback()
{
	/* print MSG on UART3 */
	char MSG[50] = "Error Code: \n";
	u32 x = CAN_voidGetErrorCode();
	MUSART_voidTransmitArr(UART3,(u8*)MSG);
	USART_voidmsgint(UART3,x);
	MUSART_voidTransmitArr(UART3,(u8*)"\r\n");
}



/**********************************************************tuning ******************************************************/



void test_tuning(PID_str* pid)
{
	pid->KP = 4 ;
	pid->Tau = 60;

	pid->Max_Input = 100;
	pid->Min_Input = -100;
	pid->Max_Output = 60000;
	pid->Min_Output = -60000;

	PID_Init(pid);
}


/**********************************************************debug ******************************************************/

void debug(void)
{

	MUSART_voidTransmitArr(UART3,(u8*)"RPM1 =  ");
	USART_voidmsgint(UART3,RPM1);
	MUSART_voidTransmitArr(UART3,(u8*)"\r\t");


	MUSART_voidTransmitArr(UART3,(u8*)"count1 =  ");
	USART_voidmsgint(UART3,count_1);
	MUSART_voidTransmitArr(UART3,(u8*)"\r\t");

	MUSART_voidTransmitArr(UART3,(u8*)"set point =  ");
	USART_voidmsgint(UART3,pid1.SetPoint);
	MUSART_voidTransmitArr(UART3,(u8*)"\r\t");

	MUSART_voidTransmitArr(UART3,(u8*)"RPM2 =  ");
	USART_voidmsgint(UART3,RPM2);
	MUSART_voidTransmitArr(UART3,(u8*)"\r\t");


	MUSART_voidTransmitArr(UART3,(u8*)"set point =  ");
	USART_voidmsgint(UART3,pid2.SetPoint);
	MUSART_voidTransmitArr(UART3,(u8*)"\r\t");


	MUSART_voidTransmitArr(UART3,(u8*)"count2 =  ");
	USART_voidmsgint(UART3,count_2);
	MUSART_voidTransmitArr(UART3,(u8*)"\r\n");
}



int main()
{
	u8 Local_Crash = 0;

	/* Rcc init & peripherals Enable */
	MRCC_voidInit();
	MRCC_voidPeripheralClockEnable(RCC_APB2,GPIOA);
	MRCC_voidPeripheralClockEnable(RCC_APB2,GPIOB);
	MRCC_voidPeripheralClockEnable(RCC_APB2,GPIOC);
	MRCC_voidPeripheralClockEnable(RCC_APB1,TIM2);

	/* STK init and millis   */

	MSTK_voidInit();
	STK_voidStartMillis();

	/* MOTORS configration pins   */
	MGPIO_voidSetPinMode(M1_port,M1_pin,GPIO_AF_OUTPUT_PP_50MHZ);
	MGPIO_voidSetPinMode(M2_port,M2_pin,GPIO_AF_OUTPUT_PP_50MHZ);
	MGPIO_voidSetPinMode(M3_port,M3_pin,GPIO_AF_OUTPUT_PP_50MHZ);
	MGPIO_voidSetPinMode(M4_port,M4_pin,GPIO_AF_OUTPUT_PP_50MHZ);

	/* */
	MGPIO_voidSetPinMode(PORTA,PIN0,GPIO_GP_OUTPUT_PP_10MHZ);
	MGPIO_voidSetPinMode(PORTB,PIN12,GPIO_GP_OUTPUT_PP_10MHZ);

	/* UART init   */
	MUSART_voidInitialization(UART3);

	/*CAN configrations*/

	/* CAN init */
	CAN_voidInit();
	/* CAN Filter set */
	CAN_FilterConfig();
	CAN_Interrupt();
	/* CAN Start */
	CAN_voidStart();



	/*Encoder & PID set configrations*/

	Encoder_1.Encoder_A_port=encoder1_front_port;
	Encoder_1.Encoder_A_pin=encoder1_front_pin;
	Encoder_1.Encoder_B_port=encoder1_back_port;
	Encoder_1.Encoder_B_pin=encoder1_back_pin;
	Encoder_init(&Encoder_1);
	Encoder_1.resolution=2020;


	Encoder_2.Encoder_A_port=encoder2_front_port;
	Encoder_2.Encoder_A_pin=encoder2_front_pin;
	Encoder_2.Encoder_B_port=encoder2_back_port;
	Encoder_2.Encoder_B_pin=encoder2_back_pin;
	Encoder_init(&Encoder_2);
	Encoder_2.resolution=2020;


	/* PID set configrations*/

	test_tuning(&pid1);
	test_tuning(&pid2);
	MTIM_voidInit();




	MGPIO_voidSetPinMode(PORTC,PIN13,GPIO_GP_OUTPUT_PP_2MHZ);  // Enable led 13
	while(1)
	{

		//				/* CAN	TX call	*/
		//		CAN_TX();
		//		MSTK_voidSetBusyWait(9000000);

		//					/* CAN	RX DATA	*/
		//		MUSART_voidTransmitArr(UART3,DATA);
		//		MUSART_voidTransmitArr(UART3,(u8*)"\n");
		//



		//		if(DATA[0] == 'A')
		//				{
		//					pid1.SetPoint=100;
		//					pid2.SetPoint=100;
		//				}else if(DATA[0] == 'B')
		//				{
		//					pid1.SetPoint=50;
		//					pid2.SetPoint=50;
		//				}else if (DATA[0] == 'C')
		//				{
		//					pid1.SetPoint=0;
		//					pid2.SetPoint=0;
		//				}
		pid1.SetPoint=DATA;
		pid2.SetPoint=DATA;


		RPM_Update(&Encoder_1);
		RPM_Update(&Encoder_2);

		PID_Update(&pid1,pid1.SetPoint,RPM1);
		PID_Update(&pid2,pid2.SetPoint,RPM2);


		if(pid1.Output > 0)
		{

			/* for MDD3A cytron*/
			MTIM_voidPWMUPCh3(pid1.Output);
			MGPIO_voidSetPinValue(M4_port,M4_pin,GPIO_LOW);

			/* for 10A cytron*/
			//		MTIM_voidPWMUPCh3(pid1.Output);
			//		MTIM_voidPWMUPCh4(50000);


		}
		else
		{	/* for MDD3A cytron*/
			MTIM_voidPWMUPCh4(pid1.Output);
			MGPIO_voidSetPinValue(M3_port,M3_pin,GPIO_LOW);

			/* for 10A cytron*/
			//		MTIM_voidPWMUPCh3(pid1.Output);
			//		MTIM_voidPWMUPCh4(0);

		}


		if(pid2.Output > 0)
		{
			/* for MDD3A cytron*/
			MTIM_voidPWMUPCh1(pid2.Output);
			MGPIO_voidSetPinValue(M2_port,M2_pin,GPIO_LOW);

			/* for 10A cytron*/
			//			MTIM_voidPWMUPCh1(pid2.Output);
			//			MTIM_voidPWMUPCh2(0);


		}
		else
		{
			/* for MDD3A cytron*/
			MTIM_voidPWMUPCh2(pid2.Output);
			MGPIO_voidSetPinValue(M1_port,M1_pin,GPIO_LOW);

			/* for 10A cytron*/
			//				MTIM_voidPWMUPCh1(pid2.Output);
			//				MTIM_voidPWMUPCh2(50000);

		}

		Local_Crash = MUSART_u8Receive();
		u32 var = 100;

		if(Local_Crash == '0')
		{
			/* Turn off buzzer */
			MGPIO_voidSetPinValue(PORTB,PIN12,0);
			var = 100;
		}
		else if(Local_Crash == '1')
		{
			/* Turn on buzzer */
			MGPIO_voidSetPinValue(PORTB,PIN12,1);

			var = 60;

		}
		else if(Local_Crash == '2')
		{
			var = 0;
		}
		MSTK_voidSetBusyWait(250000);

		CAN_TX(var);

		debug();

	}

	return 0;
}



