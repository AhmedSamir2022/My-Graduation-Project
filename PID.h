/*
 * PID.h
 *
 *  Created on: Apr 19, 2023
 *      Author: moham
 */

#ifndef PID_H_
#define PID_H_
/*
KP ,KC,KD,KI, Tau : tuning parmaters

Max_Input ,Min_Input : input range
Max_Output , Min_Output : output range

setpoint : the wanted state

CurrentTime
LastTime           for calculating time by millis
delta_time

prop : propotional term
integ: integral term
deriv: derivative term
*/

#include "STD_TYPES.h"
#include "BIT_MATH.h"


typedef struct
{
	float32 Tau ,KP,KI,KD ,KC ;
	float32 Max_Input , Min_Input, Max_Output, Min_Output;


	s32 SetPoint;
	float32 Error, previous_state;
	uint32 CurrentTime, LastTime, delta_time;

	float32 Prop, Integ, Deriv ;
	s32 Output;

}PID_str;



/***********   Functions Defintion     ***********************/

/*
 * Function : initialize the PID paramerters (set the variales to zero)
 * paramerters:
 * 				pid : pointer to an the used PID object
 *
 * return:	None
 *
 * */

void PID_Init		(PID_str *pid);



/*
 * Function : Calculate the speed in RPM and control it with PID
 * paramerters:
 * 				pid : pointer to an the used PID object
 * 				setpoint : the wanted output
 * 				state: the current measurement
 *
 * return:	None
 *
 * */

void PID_Update (PID_str *pid, float32 setpoint, float32 state);



#endif /* PID_H_ */
