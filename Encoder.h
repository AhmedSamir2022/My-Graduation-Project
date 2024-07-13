/*
 * Encoder.h
 *
 *  Created on: Dec 25, 2022
 *      Author: moham
 */

#ifndef ENCODER_H_
#define ENCODER_H_

#include"BIT_MATH.h"
#include"STD_TYPES.h"
#include"GPIO_interface.h"
#include"RCC_interface.h"
#include"EXTI_interface.h"
#include"NVIC_interface.h"
#include"STK_interface.h"
#include"AFIO_interface.h"

/**
		 * ============================================================================================
		 *     								### Encoders parameters
		 *=============================================================================================

 **/
typedef struct
{

	u16 resolution;
	u8 Encoder_A_port,Encoder_A_pin,Encoder_B_port,Encoder_B_pin;
	s32 RPM;
	s32 counter , last_counter;
	uint64 current_time,last_time;
	float delta_time;
}ENcoder_x;
ENcoder_x Encoder_1;
ENcoder_x Encoder_2;
s32 count_1,count_2;;
s8 RPM1,RPM2;
uint32 finish_micros,old_time_micros,finish_millis,old_time_millis;
uint64 elapsed_time_micros,elapsed_time_millis;


	/**
			 * ============================================================================================
			 *     								### Encoders Functions
			 *=============================================================================================

	 **/

	/*
	 * function: determine & configrate the Encoder pins A and B
	 * parameters: `A_port: Encoder_A port     A pin :Encoder_A pin
	 * 				B_port: Encoder_B port     B pin :Encoder_B pin
	 * */

	void Encoder_init(ENcoder_x * Encoder);

	/*
		* function: set resolution of the Encoder
		* parameters: none
		* */
	u16 change_resolution (ENcoder_x * Encoder ,u16 s_resolution);

	/*
		 * function: get the value of the Encoder counter
		 * parameters: `none
		 * return : the counter value
		 * */
	s32 get_counter(ENcoder_x * Encoder);

	/*
			 * function: reset counter value
			 * parameters: none
			 * */
	void reset_counter();

	/*
				 * function:increase the Encoder1_counter
				 * parameters: none
				 * */
	void front_forward_ISR();



	/*
					 * function:decrease the Encoder1_counter
					 * parameters: none
					 * */
	void front_backward_ISR();

	/*
					 * function:increase the Encoder2_counter
					 * parameters: none
					 * */
		void back_forward_ISR();



		/*
						 * function:decrease the Encoder2_counter
						 * parameters: none
						 * */
		void back_backward_ISR();

	/*
	 	 	 * function:calculate the RPM of the motors by the Encoder counter value
	 	 	 * parameters: Encoder object to select encoder 1 or 2
	 	 	 * return: the RPM value
			* */

	s8 RPM_Update(ENcoder_x * Encoder);


	/*
		 	 	 * function:get the time in milesecond
		 	 	 * parameters: non
		 	 	 *  return: the non
				* */


	uint64 Millis (void);

	void overflow_millis();

	void STK_voidStartMillis(void);

#endif /* ENCODER_H_ */
