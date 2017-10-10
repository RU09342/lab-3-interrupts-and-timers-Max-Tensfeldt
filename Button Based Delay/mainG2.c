
//ButtonBasedDelayG2

#include <msp430g2231.h>
volatile unsigned int holdTime = 10000;
volatile unsigned int overflow = 0;

volatile unsigned int j;

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

        if(holdTime > 0 || overflow > 0)
        {
            P1OUT ^= (BIT0 + BIT6); // Toggle P1.0 and P1.6 using exclusive-OR

            int counter = overflow;
            while(counter > 0)
            {
                j = 65535; //value of FFFF or one overflow
                do j--;
                while(j != 0);
                counter--;
            }


            j = holdTime; // SW Delay
            do j--;
            while(j != 0);

        }
        else //is the test for the holdTime delay
        {
            P1OUT ^= (BIT0); // Toggle P1.0 using exclusive-OR

            j = 10000; // SW Delay
            do j--;
            while(j != 0);
        }
    }

}

// Port 1 interrupt service routine
#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void)
{
    holdTime = 0;
    overflow = 0;

    while(!(P1IN & BIT3))
    {

        if(holdTime < 65535)
        {
            holdTime++;
        }
        else
        {
            holdTime = 0;
            overflow++;
            P1OUT |= BIT6;
        }


    }
    P1OUT &= ~(BIT0 + BIT6); // Clear the LEDs so they start in OFF state
    P1IFG &= ~BIT3; // P1.3 IFG cleared

}

