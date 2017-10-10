Button Based Delay
Max Tensfeldt
Intro to Embedded - Section 2

The task of Button Based Delay was to control the toggle time of an LED with a button. The length of time that the button is held is the set time that the LED will toggle at. The implementation was similar via every board. When the button is held for longer than the hex value FFFF, the overflow is incremented and used later.

* MSP430G2553
LED = P1.0 and P1.6
Button = P1.3
Simply put, when button P1.3 is pressed, LED P1.0 and P1.6 toggles high and low. When the overflow integer is incremented the first time, P1.6 will go high

* MSP430FR6989
LED = P1.0 and P9.7
Button = P1.1
When button P1.1 is pressed, LED P1.0 toggles high and low. When the overflow integer is incremented the first time, P9.7 will go high; also, whenever the overflow is decremented in the blinking stage, the same LED will toggle.

* MSP430FR2311
LEDs = P1.0 and P2.0
Button = P1.1
When button P1.1 is pressed, LED P1.0 toggles high and low. When the overflow integer is incremented the first time, P2.0 will go high; also, whenever the overflow is decremented in the blinking stage, the same LED will toggle.


* MSP430FR5994
LEDs used were P1.0 and P1.1
Button = P5.5
When button P5.5 is pressed, LED P1.0 toggles high and low. When the overflow integer is incremented the first time, P1.1 will go high; also, whenever the overflow is decremented in the blinking stage, the same LED will toggle.

* MSP430F5529
LED = P1.0 and P4.7
Button = P1.1
When button P1.1 is pressed, LED P1.0 toggles high and low. When the overflow integer is incremented the first time, P4.7 will go high; also, whenever the overflow is decremented in the blinking stage, the same LED will toggle.
