/*
 * config.h
 *
 *  Created on: Feb 15, 2023
 *      Author: moham
 */

#ifndef CONFIG_H_
#define CONFIG_H_
// encoder 1
#define encoder1_front_port	PORTA
#define encoder1_front_pin 	 12
#define encoder1_back_port 	PORTA
#define encoder1_back_pin 	 15

/*
 * Encoder 2 pins in 10A cytron
 * */


//// encoder 2
//#define encoder2_front_port	PORTA
//#define encoder2_front_pin 	 11
//#define encoder2_back_port 	PORTA
//#define encoder2_back_pin 	 10


/*
 * Encoder 2 pins in MDD3A cytron
 * */

// encoder 2
#define encoder2_front_port	PORTA
#define encoder2_front_pin 	 10
#define encoder2_back_port 	PORTA
#define encoder2_back_pin 	 11

// MOTOR back left
#define M1_port	PORTA
#define M1_pin 	0
#define M2_port PORTA
#define M2_pin 	1

// MOTOR front left
#define M3_port	PORTA
#define M3_pin 	2
#define M4_port PORTA
#define M4_pin 	3


// MOTOR back Right

#define M2_pwm_port 		PORTA
#define M2_pwm_pin 			0
#define M2_direction_port	PORTA
#define M2_direction_pin 	1

// MOTOR front right
#define M1_pwm_port 		PORTA
#define M1_pwm_pin 			2
#define M1_direction_port	PORTA
#define M1_direction_pin 	3


#endif /* CONFIG_H_ */
