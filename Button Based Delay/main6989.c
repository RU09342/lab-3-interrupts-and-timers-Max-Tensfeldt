
//ButtonBasedDelay6989

#include <msp430.h>
volatile unsigned int holdTime = 10000;
volatile unsigned int overflow = 0;
volatile unsigned int j;

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode


    P1DIR |= BIT0; // Set P1.0 to output direction
    P1OUT &= ~BIT0; // Set the LEDs off
    P9DIR |= BIT7;
    P9OUT &= BIT7;


    P1REN |= BIT1; //Enables a puller-Resistor on the button-pin
    P1OUT |= BIT1; //Writes a "1" to the portpin, tellling the resistor to pullup
    P1IES |= BIT1; //Triggers when you PRESS the button
    P1IE |= BIT1; //Enables the selector-mask for generating interrupts on the relevant pin

    __enable_interrupt(); // Interrupts get enabled *here* - they were disabled thus far..



    for (;;)
    {

        if(holdTime > 0)
        {
            P1OUT ^= BIT0; // Toggle P1.0 using exclusive-OR

            int counter = overflow;
            while(counter > 0)
            {
                 j = 65535; //value of FFFF or one overflow
                 do j--;
                 while(j != 0);
                 counter--;
                 P9OUT ^= (BIT7);
            }


            j = holdTime; // SW Delay
            do j--;
            while(j != 0);

        }
        else //is the test for the holdTime delay
        {
            P9OUT ^= (BIT7);

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

    while(!(P1IN & BIT1))
    {
        if(holdTime < 65535)
        {
               holdTime++;
        }
        else
        {
               holdTime = 0;
               overflow++;
               P9OUT |= (BIT7);
        }
    }
    P1OUT &= ~BIT0; // Clear the LEDs so they start in OFF state
    P1IFG &= ~BIT1; // P1.1 IFG cleared

}
