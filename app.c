/*
 * app.c
 *
 *  Created on: Nov 22, 2012
 *  Author: nmartin
 *  main program loop
 */

#include <msp430g2231.h>
#include "pid_ctrl.h"

#define SP	80 			//Process temp setpoint
#define IMAX 1024;
#define IMIN 1;
#define ADC_SLEEP		// Sleep during ADC conversion
#define RED_LED	BIT0
#define GREEN_LED BIT6

sPID mypid;
int process_error;
int process_value;

int
main(void) {

	unsigned adc;       // ADC value
	int c, k, f;        // Temperature in degrees C, K, and F
	unsigned mv;        // ADC reading in millivolts
	unsigned int timerCount = 0;

	// stop watchdog timer
	WDTCTL = WDTPW | WDTHOLD;

   mypid->pGain = 1;
   mypid->iGain = 1;
   mypid->dGain = 0;
   mypid->iMax = IMAX;




	// set up bit 0 of P1 as output
	P1DIR |= BIT0 + BIT6;
	// initialize bit 0 of P1 to 0
	P1OUT = BIT6;
	P1OUT ^= (RED_LED + GREEN_LED);
#ifdef ADC_SLEEP
	ADC10CTL0 |= ADC10IE;       // Enable ADC conversion complete interrupt
#endif
	for (;;) {

		P1OUT ^= (RED_LED + GREEN_LED);
#ifdef ADC_SLEEP                                                                                //
		ADC10CTL0 |= (ENC | ADC10SC);               // Begin ADC conversion
		__bis_SR_register(LPM0_bits + GIE);
		// Sleep until conversion complete
#else                                                                                              //
		ADC10CTL0 &= ~ADC10IFG;// Clear conversion complete flag
		ADC10CTL0 |= (ENC | ADC10SC);// Begin ADC conversion
		while(!(ADC10CTL0 & ADC10IFG));// Wait for conversion to complete
#endif
		//conversion is complete
		adc = ADC10MEM;                         // Read ADC

		// Convert to temperature
		c = ((27069L * adc) - 18169625L) >> 16;   // Vref = 1.5V
		//c = ((45115L * adc) -  18169625L) >> 16; // Vref = 2.5V
		//
		k = ((27069L * adc) - 268467L) >> 16;     // Vref = 1.5V
		//k = ((45115L * adc) -  268467L) >> 16;   // Vref = 2.5V
		//
		f = ((48724L * adc) - 30634388L) >> 16;   // Vref = 1.5V
		//f = ((81206L * adc) -  30634388L) >> 16; // Vref = 2.5V

		// Convert to millivolts
		mv = (96094L * adc + 32768) >> 16;         // Vref = 1.5V
		//mv = (160156L * adc + 32768) >> 16;      // Vref = 2.5V

		//TODO - Do your PID control here after getting AD value

	}

}

#pragma vector = ADC10_VECTOR		// ADC conversion complete interrupt
__interrupt
void ADC10_ISR(void) {                                                               //
	__bic_SR_register_on_exit(LPM0_bits);
	// Wakeup main code
}

/* The Integer way to get high precision temps using integer math
 * From: http://forum.43oh.com/topic/1954-using-the-internal-temperature-sensor/
 * C = (A * 27069 - 18169625) >> 16
 * K = (A * 27069 - 268467) >> 16
 * F = (A * 48724 - 30634388) >> 16
 */

