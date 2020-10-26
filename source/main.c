/*	Author: roliv006
 *  Partner(s) Name: 
 *	Lab Section: 22
 *	Assignment: Lab #4  Exercise #2
 *	Exercise Description: Buttons are connected to a PA0 and PA1. Output for PORTC is initially 7. Pressing PA0 increments PORTC once
 *  (stopping at 9). Pressing PA1 decrements PORTC once (stopping at 0). If both buttons are depressed (even if not initially simultaneously)
 *  , PORTC resets to 0.
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{START, DECREMENT_RELEASE, INCREMENT_PRESS, INCREMENT_RELEASE, DECREMENT_PRESS}state;

void Tick(){
    unsigned char pinA0 = PINA && 0x01;
    unsigned char pinA1 = PINA && 0x02;
    unsigned char cnt = 0x07;

    switch(state){
        case START:
            PORTC = cnt;
            state = DECREMENT_RELEASE;
            break;
        case DECREMENT_RELEASE:
            if(pinA0){
                state = INCREMENT_PRESS;
            }else if(pinA1){
                state = DECREMENT_PRESS;
            }else{
                state = DECREMENT_RELEASE;
            }
            break;
        case INCREMENT_PRESS:
            if(pinA0){
                state = INCREMENT_PRESS;
            }else if(pinA1){
                state = DECREMENT_PRESS;
            }else{
                state = INCREMENT_PRESS;
            }
            break;
        case INCREMENT_RELEASE:
            if(pinA0){
                state = INCREMENT_PRESS;
            }else if(pinA1){
                state = DECREMENT_PRESS;
            }else{
                state = INCREMENT_RELEASE;
            }
            break;
        case DECREMENT_PRESS:
            if(pinA0){
                state = INCREMENT_PRESS;
            }else if(pinA1){
                state = DECREMENT_PRESS;
            }else{
                state = DECREMENT_PRESS;
            }
            break;
        default:
            break;
    }

    switch(state){
        case START:
            break;
        case DECREMENT_RELEASE:
            if(!pinA0 && !pinA1){
                PORTC = 0x00;
            }
            break;
        case INCREMENT_PRESS:
            if(cnt != 9){
                cnt++;
            }
            break;
        case INCREMENT_RELEASE:
            if(!pinA0 && !pinA1){
                PORTC = 0x00;
            }
            break;
        case DECREMENT_PRESS:
            if(cnt != 0){
                cnt--;
            }
            break;
        default:
            break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00;
    PORTA = 0xFF;
    DDRC = 0xFF; // Configure port C's 8 pins as outputs
    PORTC = 0x00; // Initialize PORTC output to 0's

    state = START;
    
    /* Insert your solution below */
    while (1) {
        Tick();
    }

    return 1;
}
