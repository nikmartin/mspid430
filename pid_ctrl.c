/*
*Copyright (c) 2012, Nik Martin
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification, 
* are permitted provided that the following conditions are met:
*
*    * Redistributions of source code must retain the above copyright notice, this 
*      list of conditions and the following disclaimer.
*    * Redistributions in binary form must reproduce the above copyright notice, 
*      this list of conditions and the following disclaimer in the documentation 
*      and/or other materials provided with the distribution.
*    * Neither the name of the <ORGANIZATION> nor the names of its contributors 
*      may be used to endorse or promote products derived from this software 
*      without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
* THIS ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
* THIS WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
* THIS DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE 
* THIS FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
* THIS DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
* THIS SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
* THIS CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
* THIS OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE 
* THIS USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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

