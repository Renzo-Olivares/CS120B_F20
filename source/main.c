/*	Author: roliv006
 *  Partner(s) Name: 
 *	Lab Section: 22
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: PB0 and PB1 each connect to an LED, and PB0's LED is initially on. Pressing a button connected to PA0 turns
 *  off PB0's LED and turns on PB1's LED, staying that way after button release. Pressing the button again turns off PB1's LED and turns
 *  on PB0's LED.
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{START, OFF_RELEASE, ON_PRESS, ON_RELEASE, OFF_PRESS}state;

void Tick(){
    unsigned char pinA0 = PINA && 0x01;

    switch(state){
        case START:
            B = 0x01;
            state = OFF_RELEASE;
            break;
        case OFF_RELEASE:
            state = pinA0? ON_PRESS : OFF_RELEASE;
            break;
        case ON_PRESS:
            state = pinA0? ON_PRESS : ON_RELEASE;
            break;
        case ON_RELEASE:
            state = pinA0? OFF_PRESS: ON_RELEASE;
            break;
        case OFF_PRESS:
            state = pinA0? OFF_PRESS : OFF_RELEASE;
            break;
        default:
            break;
    }

    switch(state){
        case START:
            break;
        case OFF_RELEASE:
            break;
        case ON_PRESS:
            B = 0x02;
            break;
        case ON_RELEASE:
            break;
        case OFF_PRESS:
            B = 0x01;
            break;
        default:
            break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00;
    PORTA = 0xFF;
    DDRB = 0xFF; // Configure port B's 8 pins as outputs
    PORTB = 0x00; // Initialize PORTB output to 0's

    state = START;
    
    /* Insert your solution below */
    while (1) {
        Tick();
    }

    return 1;
}
