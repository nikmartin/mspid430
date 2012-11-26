/*
 * pid_ctrl.c
 *
 *  Created on: Nov 22, 2012
 *      Author: somewebguy
 *      The following is a pretty basic C PID controller, but it has
 *      worked very well with good stability when tuned correctly.
 *      The code doesn't have a lot of features and uses a independent
 *      gains equation, but you can dress it up or down as much as you
 *      want.  I just pasted it from another application, adapt as needed.
 *
 */

#include <stdlib.h>
#include "pid_ctrl.h"

/**
 * update_pid
 * Author: Nik Martin, original code from Tim Wescott
 * Description: update_pid is called on each loop of the sample routine that
 * samples the PV (Process Value). It could be loop based, but timer interrupts
 * will give more accurate results
 * Arguments: 	sPID - The PID struct
 * 				pe - Process Error (PV-SP=PE)
 * 				pv - Process Value
 * Returns: int of value to send to control system
 */
int
update_pid(sPID * pid, int pe, int pv) {

	int pTerm, iTerm, dTerm;

	// calculate the proportional term
	pTerm = pid->pGain * pe;

	// calculate the integral state
	pid->iState += pe;
	//now limit the integral if out of bounds
	if (pid->iState > pid->iMax)
		pid->iState = pid->iMax;
	else if (pid->iState < pid->iMin)
		pid->iState = pid->iMin;
	// calculate the integral term
	iTerm = pid->iGain * pid->iState;

	// now calculate derivative term
	// this method also eliminates "Derivative Kick"
	dTerm = pid->dGain * (pv - pid->dState);
	//set last value of dState to current value for the next loop
	pid->dState = pv;
	return (pTerm + iTerm - dTerm);
}

