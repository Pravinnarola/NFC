#include <msp430.h>				


/**
 * blink.c
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;		// stop watchdog timer
	P1DIR |= 0x01;                  // configure P1.0 as output
	P1DIR |= 0x40;                  // configure P1.6 as output

	volatile unsigned int i;		// volatile to prevent optimization

	while(1)
	{
		P1OUT ^= 0x01;				// toggle P1.0
		P1OUT ^= 0x40;              // toggle P1.6
		for(i=50000; i>0; i--);     // delay
	}
}
