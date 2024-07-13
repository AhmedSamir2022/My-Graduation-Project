/*
 * Encoder.c
 *
 *  Created on: Dec 25, 2022
 *      Author: moham
 */

#include <stdio.h>
#include <stdlib.h>
#include "Encoder.h"
#include"GPIO_interface.h"
#include "config.h"
#include "USART_interface.h" // FOR DEBUGE

/*
	 * function: determine & configrate the Encoder pins A and B
	 * parameters: `A_port: Encoder_A port     A pin :Encoder_A pin
	 * 				B_port: Encoder_B port     B pin :Encoder_B pin
	 * */




//
//
//	u16 resolution;
//	u8 Encoder_A_port,Encoder_A_pin,Encoder_B_port,Encoder_B_pin;
//	u32 RPM;
//	u32 counter , last_counter;
//	u32 current_time,last_time;
//	float delta_time;
//
//
//

	void Encoder_init(ENcoder_x * Encoder)
	{
		Encoder->counter=0;
			// RCC configrations
		MRCC_voidPeripheralClockEnable(RCC_APB2,Encoder->Encoder_A_port);
		MRCC_voidPeripheralClockEnable(RCC_APB2,Encoder->Encoder_B_port);
		// GPIO configrations
		MGPIO_voidSetPinMode(Encoder->Encoder_A_port,Encoder->Encoder_A_pin,GPIO_INPUT_PU_PD);
		MGPIO_voidSetPinValue(Encoder->Encoder_A_port,Encoder->Encoder_A_pin,GPIO_LOW);
		MGPIO_voidSetPinMode(Encoder->Encoder_B_port,Encoder->Encoder_B_pin,GPIO_INPUT_PU_PD);
		MGPIO_voidSetPinValue(Encoder->Encoder_B_port,Encoder->Encoder_B_pin,GPIO_LOW);
		// AFIO configrations
		MAFIO_voidEXTIConfiguration(Encoder->Encoder_A_pin,Encoder->Encoder_A_port);
		MAFIO_voidEXTIConfiguration(Encoder->Encoder_B_pin,Encoder->Encoder_B_port);
		//EXTI configrations
		EXTI_voidSelectTrig(Encoder->Encoder_A_pin,EXTI_BOTH_TRIGGER);
		EXTI_voidControlLine(Encoder->Encoder_A_pin, EXTI_ENABLE);
		EXTI_voidSelectTrig(Encoder->Encoder_B_pin,EXTI_BOTH_TRIGGER);
		EXTI_voidControlLine(Encoder->Encoder_B_pin, EXTI_ENABLE);
		// NVIC Enable EXTI
		MNVIC_voidInit();
		MNVIC_EnableInterrupt(40);  // INT 10----> 15

		if(Encoder->Encoder_A_pin == Encoder_1.Encoder_A_pin){
					MUSART_voidTransmitArr(UART3,(u8*)"\r\n");
					EXTI_voidSetCallBack(Encoder->Encoder_A_pin,front_forward_ISR);
					EXTI_voidSetCallBack(Encoder->Encoder_B_pin,front_backward_ISR);

				}else {
							MUSART_voidTransmitArr(UART3,(u8*)"\r\n");
					EXTI_voidSetCallBack(Encoder->Encoder_A_pin,back_forward_ISR);
					EXTI_voidSetCallBack(Encoder->Encoder_B_pin,back_backward_ISR);

				}
	}



	/*
		* function: set resolution of the Encoder
		* parameters: Encoder object
		* 				s_resolution : the new resolution
		* */
		/*
		 * function: get the value of the Encoder counter
		 * parameters: `none
		 * return : the counter value
		 * */
	u16 change_resolution (ENcoder_x * Encoder , u16 s_resolution)
	{
	  if(s_resolution>0)
		{
		  Encoder->resolution=s_resolution;
		}

	 return Encoder->resolution;
	}



	s32 get_counter(ENcoder_x * Encoder)
		{
			if(Encoder->Encoder_A_pin == Encoder_1.Encoder_A_pin)
			{
				return count_1;
			}else
			{
				return count_2;
			}
		}



	/*
			 * function: reset counter value
			 * parameters: none
			 * */
	void reset_counter(ENcoder_x * Encoder){
		Encoder->counter=0;
	}




	/*
				 * function:increase the Encoder_counter
				 * parameters: none
				 * */
	void front_forward_ISR()
	{
		u8 a,b;
		a= MGPIO_u8GetPinValue(encoder1_front_port,encoder1_front_pin);
		b=MGPIO_u8GetPinValue(encoder1_back_port,encoder1_back_pin);

			if(a != b)
				Encoder_1.counter++;
			else
				Encoder_1.counter--;

			count_1=Encoder_1.counter;

/******************************************DEBUGE************************************************/
			//USART_voidmsgstring((s32*)"front_forward       ");

	}




	/*
					 * function:decrease the Encoder_counter
					 * parameters: none
					 * */
	void front_backward_ISR()
	{
		u8 a,b;
				a= MGPIO_u8GetPinValue(encoder1_front_port,encoder1_front_pin);
				b=MGPIO_u8GetPinValue(encoder1_back_port,encoder1_back_pin);

					if(a == b)
						Encoder_1.counter++;
					else
						Encoder_1.counter--;

					count_1=Encoder_1.counter;

/******************************************DEBUGE************************************************/
					//USART_voidmsgstring((s32*)"front_backward       ");
	}




	/*
					 * function:increase the Encoder_counter
					 * parameters: none
					 * */
	void back_forward_ISR()
		{
		u8 a,b;
				a= MGPIO_u8GetPinValue(encoder2_front_port,encoder2_front_pin);
				b=MGPIO_u8GetPinValue(encoder2_back_port,encoder2_back_pin);

					if(a != b)
						Encoder_2.counter++;
					else
						Encoder_2.counter--;

					count_2=Encoder_2.counter;

/******************************************DEBUGE************************************************/
					//USART_voidmsgstring((s32*)"back_forward in ISR      ");

					//USART_voidmsgint(UART3,Encoder_2.counter);
					//USART_voidmsgstring((s32*)"        ");
					//USART_voidmsgstring((s32*)"\r\n");
					//MUSART_voidTransmitArr(UART3,"\r\n");

		}





		/*
						 * function:decrease the Encoder_counter
						 * parameters: none
						 * */
	void back_backward_ISR()
	{
		u8 a,b;
						a= MGPIO_u8GetPinValue(encoder2_front_port,encoder2_front_pin);
						b=MGPIO_u8GetPinValue(encoder2_back_port,encoder2_back_pin);

							if(a == b)
								Encoder_2.counter++;
							else
								Encoder_2.counter--;

							count_2=Encoder_2.counter;
/******************************************DEBUGE************************************************/

		//USART_voidmsgstring((s32*)"back_backward       ");
		//USART_voidmsgint(UART3,Encoder_2.counter);
		//USART_voidmsgstring((s32*)"        ");
		//USART_voidmsgstring(UART1,(s32*)"\r\n");
		//MUSART_voidTransmitArr(UART3,(u8*)"\r\n");

	}


	/*
		 	 	 * function:calculate the RPM of the motors by the Encoder counter value
		 	 	 * parameters: Encoder object to select encoder 1 or 2
		 	 	 * return: the RPM value
				* */
	s8 RPM_Update(ENcoder_x * Encoder)
	{

		Encoder->current_time=Millis();
		Encoder->delta_time=((Encoder->current_time - Encoder->last_time)*1.0);   // delta in seconds
		if(Encoder->Encoder_A_pin == Encoder_1.Encoder_A_pin)
					{
					Encoder->counter= count_1;
					}else
					{
					Encoder->counter=count_2;
					}
		Encoder->RPM=(( (Encoder->counter-Encoder->last_counter) *1.0*(1000*60)) / (Encoder->resolution * Encoder->delta_time));
		Encoder->last_time=Encoder->current_time;
		Encoder->last_counter=Encoder->counter;
		if(Encoder->Encoder_A_pin == Encoder_1.Encoder_A_pin)
					{
						RPM1=Encoder->RPM;
						return RPM1;
					}else

					{
						RPM2=Encoder->RPM;
						return RPM2;
					}

	}



	void overflow_millis(){


	elapsed_time_millis += 16000000/9000.0 - finish_millis;
	old_time_millis =0;

	}


	void STK_voidStartMillis(void)
	{

		MSTK_voidSetIntervalPeriodic(16000000,overflow_millis);

	}

	uint64 Millis(void)
	{

	  finish_millis = MSTK_u32GetElapsedTime()/9000.0;
		elapsed_time_millis += finish_millis - old_time_millis;
	  old_time_millis = finish_millis;

	return elapsed_time_millis;
	}


