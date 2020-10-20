/*	Author: roliv006
 *      Partner(s) Name: 
 *	Lab Section: 22
 *	Assignment: Lab #3  Exercise #1
 *	Exercise Description: Count the number of 1s on ports A and B and output that number on port C.
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    DDRA = 0x00;
    PORTA = 0xFF;
    DDRB = 0x00;
    PORTB = 0xFF;
    DDRC = 0xFF;
    PORTC = 0x00; 

    while (1) {
        unsigned char total = 0x00;
        unsigned char pinA0 = (PINA & 0x01);
        unsigned char pinA1 = (PINA & 0x02) >> 1;
        unsigned char pinA2 = PINA & 0x04 >> 2;
        unsigned char pinA3 = PINA & 0x08 >> 3;
        unsigned char pinA4 = PINA & 0x10 >> 4;
        unsigned char pinA5 = PINA & 0x20 >> 5;
        unsigned char pinA6 = PINA & 0x40 >> 6;
        unsigned char pinA7 = PINA & 0x80 >> 7;
        unsigned char pinB0 = PINB & 0x01;
        unsigned char pinB1 = PINB & 0x02 >> 1;
        unsigned char pinB2 = PINB & 0x04 >> 2;
        unsigned char pinB3 = PINB & 0x08 >> 3;
        unsigned char pinB4 = PINB & 0x10 >> 4;
        unsigned char pinB5 = PINB & 0x20 >> 5;
        unsigned char pinB6 = PINB & 0x40 >> 6;
        unsigned char pinB7 = PINB & 0x80 >> 7;
        total = pinA0 + pinA1 + pinA2 + pinA3 + pinA4 + pinA5 + pinA6 + pinA7 + pinB0 + pinB1 + pinB2 + pinB3 + pinB4 + pinB5 + pinB6 + pinB7;

        PORTC = total;
    }

    return 1;
}
