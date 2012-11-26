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


#ifndef PID_CTRL_H_
#define PID_CTRL_H_


struct sPID_TAG;
/** The sPID structure gets passed around, and is persistent, since it holds
 historical values. You need to use Digital values in here since this is all
 integer math.
 */
typedef struct sPID_TAG{
	int dState;		// Last pv input
	int iState;     // Integrator state - accumulated error
	int iMax, iMin; // Integrator limits
	int pGain,    	// Proportional gain
			iGain,  // Integral gain
			dGain;  // Derivative gain
}sPID;


int
update_pid(sPID * pid, int pe, int pv);

#endif /* PID_CTRL_H_ */
