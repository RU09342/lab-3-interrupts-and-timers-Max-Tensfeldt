
//ButtonInterruptG2

#include <msp430g2231.h>

unsigned int blink = 0;

void main(void)
{
WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer


P1DIR |= (BIT0 + BIT6); // Set P1.0 and P1.6 to output direction
P1OUT &= ~(BIT0 + BIT6); // Set the LEDs off


P1REN |= BIT3; //Enables a puller-Resistor on the button-pin
P1OUT |= BIT3; //Writes a "1" to the portpin, tellling the resistor to pullup
P1IES |= BIT3; //Triggers when you PRESS the button
P1IE |= BIT3; //Enables the selector-mask for generating interrupts on the relevant pin

__enable_interrupt(); // Interrupts get enabled *here* - they were disabled thus far..

for (;;)
{

    if(blink > 0)
    {
        P1OUT ^= (BIT0 + BIT6); // Toggle P1.0 and P1.6 using exclusive-OR

        __delay_cycles(100000); // SW Delay of 10000 cycles at 1Mhz

    }
}

}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    blink ^= 0x01;
    P1IFG &= ~BIT3; // P1.3 IFG cleared
    P1OUT &= ~(BIT0 + BIT6); // Clear the LEDs so they start in OFF state

}

