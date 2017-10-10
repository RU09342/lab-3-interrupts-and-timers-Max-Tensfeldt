Button Interrupt
Max Tensfeldt
Intro to Embedded - Section 2

The task of button interrupt was to have a button toggle a led using interrupts. The code for each was very similar as the only thing that had to be done was interrupt the loop that runs an LED at high or low till a button is pressed.

* MSP430G2553
LED = P1.0
Button = P1.3
Simply put, when button P1.3 is pressed, LED P1.0 toggles high and low

* MSP430F5529
LED = P1.0
Button = P1.1
When button P1.1 is pressed, LED P1.0 toggles high and low

* MSP430FR2311
LEDs = P1.0
Button = P1.1
When button P1.1 is pressed, LED P1.0 toggles high and low


* MSP430FR5994
LEDs used were P1.0
Button = P5.5
When button P5.5 is pressed, LED P1.0 toggles high and low

* MSP430FR6989
LED = P1.0
Button = P1.1
When button P1.1 is pressed, LED P1.0 toggles high and low

