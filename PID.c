/*
 * PID.c
 *
 *  Created on: Apr 19, 2023
 *      Author: moham
 */

#include "PID.h"
#include "Encoder.h"



void  PID_Init(PID_str *pid)
{
	/* Clear controller variables */
	pid->CurrentTime = 0;
	pid->LastTime = 0;
	pid->delta_time = 0;

	pid->Prop = 0;
	pid->Integ = 0;
	pid->Deriv = 0;

	pid->Error = 0;

	pid->Output = 0;
	pid->previous_state = 0;

	pid->KC = (1/pid->KP) * (pid->Max_Output) / (pid->Max_Input);

	pid->KI = 1;
	pid->KD = 0;

}


void PID_Update(PID_str *pid, float32 setpoint, float32 state)
{

	/* calculate the delta time */
	pid->CurrentTime = Millis();
	pid->delta_time = pid->CurrentTime - pid->LastTime;

	/* calculate the error */
	pid->Error = setpoint - state;


	/*** Calculate each PID term separately ***/

	/* calculate the Propotional */
	pid->Prop = pid->KC * pid->Error;

	/* calculate the Integral */
	pid->Integ += pid->KI * pid->Error * pid->delta_time * pid->KC / pid->Tau;

	/* calculate the Derivative */
	/* mines(-1) beacause  of Derivative Kick */
	pid->Deriv = -1 * pid->KD * pid->KC * pid->Tau * (state - pid->previous_state) / pid->delta_time;


	/* Calculate the output by summing the 3 Terms */
	pid->Output = pid->Prop +  pid->Integ + pid->Deriv;

	// Constrain Output_Value
	if(pid->Output > pid->Max_Output)
	{
		pid->Output = pid->Max_Output;

		/* Anti-Reset Windup */
		/* undo previous accumlation of the Integral Term to prevent the variable from exploding */
		pid->Integ -= 2* pid->Error * pid->delta_time * pid->KC / pid->Tau;
	}
	else if (pid->Output < pid->Min_Output)
	{
		pid->Output = pid->Min_Output;

		/* Anti-Reset Windup */
		/* undo previous accumlation of the Integral Term to prevent the variable from exploding */
		pid->Integ -= 2* pid->Error * pid->delta_time * pid->KC / pid->Tau;
	}
	 /* Update variables */
	pid->previous_state = state;
	pid->LastTime = pid->CurrentTime;

}
