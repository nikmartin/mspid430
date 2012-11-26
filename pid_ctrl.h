/*
 * pid_ctrl.h
 *
 *  Created on: Nov 25, 2012
 *      Author: nmartin
 */

#ifndef PID_CTRL_H_
#define PID_CTRL_H_

/* The sPID structure gets passed around, and is persistent, since it holds
 historical values. You need to use Digital values in heresince this is all
 integer math.
 */
struct sPID_TAG;
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
