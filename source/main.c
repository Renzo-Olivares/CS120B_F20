/*	Author: roliv006
 *  Partner(s) Name: 
 *	Lab Section: 22
 *	Assignment: Lab #6  Exercise #1
 *	Exercise Description: Create a synchSM to blink three LEDs connected to PB0, PB1, and PB2
 *  in sequence, 1 second each. Implement that synchSM in C using the method defined in class. 
 *  In addition to demoing your program, you will need to show that your code adheres entirely 
 *  to the method with no variations.
 * 
 *  To clarify and match the video, the lights should turn on in the following sequence:
 *  PB0,PB1,PB2,PB0,PB1,PB2,PB0,PB1,PB2…
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{START, INIT, NEXT}state;
unsigned char out;

void Tick() {
    // State transition
    switch(state){
        case START:
            state = INIT;
            break;
        case INIT:
            state = NEXT;
            break;
        case NEXT:
            state = NEXT;
            break;
        default:
            break;
    }

    // State actions
    switch(state){
        case INIT:
            PORTB = out = 0x01;
            break;
        case NEXT:
            out = (out == 0x04) ? 0x01 : out << 1;
            PORTB = out;
            break;
        default:
            break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0xFF; // Set port B to output
    PORTB = 0x00; // Init port B to 0s
    state = START;
    TimerSet(1000);
    TimerOn();

    /* Insert your solution below */
    while (1) {
        // User code (i.e. syncSM calls)
        Tick();
        while(!TimerFlag); // Wait 1 SEC
        TimerFlag = 0;
        // Note: For the above a better style would use a syncSm with TickSM()
        // This example just illsutrates the use of the ISR and flag
    }
    return 1;
}
