#include <msp430g2553.h>

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;
    P1DIR = BIT6;  //  P1.6to input direction
    P1REN = BIT3; //P 1.3 Resistor Enable
    P1OUT = BIT3;//P 1.3 Output
    P1IE = BIT3; // P1.3 interrupt enabled
    __enable_interrupt();
    while(1){  }
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    __delay_cycles(500000); //delay
    P1OUT ^= BIT6;
    P1IFG = ~BIT3; // P1.3 interrupt flag cleared
}
