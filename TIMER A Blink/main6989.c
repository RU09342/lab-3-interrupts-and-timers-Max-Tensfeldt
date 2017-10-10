
//TimerABlink6989

#include <msp430.h>

unsigned int timerCount = 0;
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode


    P1DIR |= BIT0; // Set P1.0 to output direction
    P1OUT &= ~BIT0; // Set the LEDs off

    TA0CCTL0 = CCIE;
    TA0CTL = TASSEL_2 + MC_2; // Set the timer A to SMCLCK, Continuous
    // Clear the timer and enable timer interrupt

    __enable_interrupt();

    __bis_SR_register(LPM0 + GIE); // LPM0 with interrupts enabled

}


// Timer A0 interrupt service routine
#pragma vector = TIMER0_A0_VECTOR

__interrupt void Timer_A (void)
{
    timerCount = (timerCount + 1) % 8;
    if(timerCount == 0)
    {
        P1OUT ^= BIT0;
    }
}
