#include <msp430g2553.h>

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD; //Disable the Watchdog timer for our convenience.

    P1DIR |= BIT2; //Set pin 1.2 to the output direction.
    P1SEL |= BIT2;//Select pin 1.2 as our PWM output.
    P1REN |= BIT3;//enable pull up/down reg
    P1OUT |= BIT3;//p1.3 is set as output
    P1IE |= BIT3; // interrupt enable on p1.3




    PWM(130,60);   //Give input PWM(frequency,pulse_width)


    TA0CTL = TASSEL_2 + MC_1; //TASSEL_2 selects SMCLK as the clock source, and MC_1 tells it to count up to the value in TA0CCR0.
    __enable_interrupt();
    __bis_SR_register(LPM0_bits); //Switch to low power mode 0.
    while(1)
    { }
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    __delay_cycles(500000);
    P1SEL &= ~BIT2;   //turn off p1.2
    P1IFG &= ~BIT3;   //clear interrupt flag on p1.3

}
void PWM(int f,int PW)
{
TA0CCR0 = 1000000 / f; //Set the period in the Timer A0 Capture/Compare 0 register to given frequency value.
TA0CCTL1 = OUTMOD_7;/* PWM output mode: 7 - PWM reset/set */
TA0CCR1 = PW; //The period in microseconds that the power is ON.
}
