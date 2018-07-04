#include <msp430g2553.h>

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD; //Disable the Watchdog timer for our convenience.

    P1DIR |= BIT2; //Set pin 1.2 to the output direction.
    P1SEL |= BIT2; //Select pin 1.2 as our PWM output.

    PWM(130,60);   //Give input PWM(frequency,pulse_width)


    TA0CTL = TASSEL_2 + MC_1; //TASSEL_2 selects SMCLK as the clock source, and MC_1 tells it to count up to the value in TA0CCR0.

    __bis_SR_register(LPM0_bits); //Switch to low power mode 0.
}

void PWM(int f,int PW)
{
TA0CCR0 = 1000000 / f; //Set the period in the Timer A0 Capture/Compare 0 register to given frequency value.
TA0CCTL1 = OUTMOD_7;/* PWM output mode: 7 - PWM reset/set */
TA0CCR1 = PW; //The period in microseconds that the power is ON.
}

