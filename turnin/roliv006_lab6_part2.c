/*	Author: roliv006
 *  Partner(s) Name: 
 *	Lab Section: 22
 *	Assignment: Lab #6  Exercise #2
 *	Exercise Description: Create a simple light game that requires pressing a button on PA0 
 *  while the middle of three LEDs on PB0, PB1, and PB2 is lit. The LEDs light for 300 ms 
 *  each in sequence. When the button is pressed, the currently lit LED stays lit. Pressing 
 *  the button again restarts the game. 
 * 
 *  To clarify and match the video, the lights should turn on in the following sequence:
 *  PB0,PB1,PB2,PB1,PB0,PB1,PB2,PB1,PB0…
 * 
 *  Demo Link: https://youtu.be/YsNXu2J-jm4
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{START, INIT, NEXT, NEXT_REVERSE, HOLD_PRESS, HOLD_RELEASE}state;
unsigned char out;
unsigned char button;

void Tick() {
    button = ~PINA & 0x01;
    
    // State transition
    switch(state){
        case START:
            state = INIT;
            break;
        case INIT:
            state = NEXT;
            break;
        case NEXT:
            if(button){
                state = HOLD_PRESS;
            }else{
                state = (out == 0x04) ? NEXT_REVERSE : NEXT;
            }
            break;
        case NEXT_REVERSE:
            if(button){
                state = HOLD_PRESS;
            }else{
                state = (out == 0x01) ? NEXT : NEXT_REVERSE;
            }
            break;
        case HOLD_PRESS:
            state = button? HOLD_PRESS : HOLD_RELEASE;
            break;
        case HOLD_RELEASE:
            state = button? INIT : HOLD_RELEASE;
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
            out = out << 1;
            PORTB = out;
            break;
        case NEXT_REVERSE:
            out = out >> 1;
            PORTB = out;
            break;
        case HOLD_PRESS:
            break;
        case HOLD_RELEASE:
            break;
        default:
            break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0xFF; // Set port B to output
    DDRA = 0x00;
    PORTB = 0x00; // Init port B to 0s
    PORTA = 0xFF;
    state = START;
    TimerSet(300);
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
