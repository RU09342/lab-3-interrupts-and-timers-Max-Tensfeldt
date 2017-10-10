
//ButtonInterrupt5994

#include <msp430.h>

void main (void)
{
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode

    P1DIR |= BIT0;                            // Set P1.0 to output direction
    P1OUT &= ~BIT0;

    P5REN |= BIT5;                            // Enable P5.5 internal resistance
    P5OUT |= BIT5;                            // Set P5.5 as pull-Up resistance
    P5IES &= ~BIT5;                           // P5.5 Lo/Hi edge
    P5IFG &= ~BIT5;                           // P5.5 IFG cleared
    P5IE |= BIT5;                             // P5.5 interrupt enabled

    __bis_SR_register( GIE );                 // Enable interrupts globally

    while(1)
    {
        __no_operation();                     // Placeholder for while loop (not required)

    }
}

// Port 1 interrupt service routine
#pragma vector=PORT5_VECTOR
__interrupt void Port_1(void)
{
    switch( __even_in_range( P5IV, P5IV_P5IFG7 ))
    {
        case P5IV_P5IFG5:      // Pin 5 (button 5)
            P1OUT^=BIT0;
            int j = 0;
            do j++;
            while(j != 10000);
            P1IFG &= ~BIT1;
            break;
        default:   _never_executed();



    }

}
