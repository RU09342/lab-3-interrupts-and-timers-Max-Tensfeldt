
//TimerABlink2311

#include <msp430.h> 


/**
 * main.c
 */
unsigned int timerCount = 0;
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode

    P1DIR |= BIT0; // Set P1.0 to output direction
    P1OUT &= ~BIT0; // Set the LEDs off

    TB0CCTL0 = CCIE;
    TB0CTL |= TBSSEL__SMCLK | MC__CONTINUOUS; // Set the timer A to SMCLCK, Continuous
    // Clear the timer and enable timer interrupt

    __enable_interrupt();

    __bis_SR_register(LPM0 + GIE); // LPM0 with interrupts enabled

}


// Timer B0 interrupt service routine
#pragma vector = TIMER0_B0_VECTOR

__interrupt void Timer_B (void)
{
    timerCount = (timerCount + 1) % 8;
    if(timerCount == 0)
    {
        P1OUT ^= BIT0;
    }
}
