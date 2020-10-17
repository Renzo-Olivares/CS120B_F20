/*	Author: roliv006
 *  Partner(s) Name: 
 *	Lab Section: 22
 *	Assignment: Lab #2  Exercise #1
 *	Exercise Description: Garage open at night -- A garage door sensor connects to PA0 (1 means door open), and a light sensor
 *  connects to PA1(1 means light is sensed). Write a program that illuminates an LED connected to PB0(1 means illuminate) if the
 *  garage door is open at night.
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {START, OFF, ON}state;
void Tick(){
    unsigned char pinA0 = PINA & 0x00;
    unsigned char pinA1 = PINA & 0x01;

    switch(state){
        case START:
            state = OFF;
            break;
        case OFF:
            if(!pinA0 || pinA1){
                state = OFF;
            }
            if(pinA0 && !pinA1){
                state = ON;
            }
            break;
        case ON:
            if(pinA0 && !pinA1){
                state = ON;
            }
            if(!pinA0 || pinA1){
                state = OFF;
            }
            break;
        default:
            break;
    }

    switch(state){
        case START:
            break;
        case OFF:
            PORTB = 0x00;
            break;
        case ON:
            PORTB = 0x01;
            break;
        default:
            break;
    }
}

int main(void) {
    DDRA = 0x00;
    PORTA = 0xFF;
    DDRB = 0xFF;
    PORTB = 0x00;

    state = START;

    while(1){
        Tick();
    }

    return 1;
}
