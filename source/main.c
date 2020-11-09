/*	Author: renzo
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0xFF; // Set port B to output
    PORTB = 0x00; // Init port B to 0s
    TimerSet(1000);
    TimerOn();
    unsigned char tmpB = 0x00;
    /* Insert your solution below */
    while (1) {
        // User code (i.e. syncSM calls)
        tmpB = ~tmpB; //Toggle PORTB; Temporary, bad programming style
        PORTB = tmpB;
        while(!TimerFlag); // Wait 1 SEC
        TimerFlag = 0;
        // Note: For the above a better style would use a syncSm with TickSM()
        // This example just illsutrates the use of the ISR and flag
    }
    return 1;
}
