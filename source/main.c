/*	Author: roliv006
 *      Partner(s) Name: 
 *	Lab Section: 22
 *	Assignment: Lab #3  Exercise #2
 *	Exercise Description: A car has a fuel-level sensor that sets PA3..PA0 to a value between 0 (empty) and 15 (full). A series
 *  of LEDs connected to PC%..PC0 should light to graphically indicate the fuel level. If the fuel level is 1 or 2, PC5 lights.
 *  If the level is 3 or 4, PC5 and PC4 light. Level 5-6 PC5..PC3. 7-9 PC5..PC2. 10-12 lights PC5..PC1. 13-15 lights PC5..PC0.
 *  Also, PC6 connects to a "Low fuel" icon, which should light if the level is 4 or less. 
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
    DDRC = 0xFF;
    PORTC = 0x00; 
    
    while (1) {
        unsigned char pinA0 = PINA & 0x01;
        unsigned char pinA1 = PINA & 0x02;
        unsigned char pinA2 = PINA & 0x04;
        unsigned char pinA3 = PINA & 0x08;

        unsigned char fuellevel = pinA0 + pinA1 + pinA2 + pinA3;

        switch(fuellevel){
            case 0x01:
            case 0x02:
                //light PC5
                //light low fuel
                PORTC = 0x60;
                break;
            case 0x03:
            case 0x04:
                //light PC5 and PC4
                //light low fuel
                PORTC = 0x70;
                break;
            case 0x05:
            case 0x06:
                //light PC5..PC3
                PORTC = 0x38;
                break;
            case 0x07:
            case 0x08:
            case 0x09:
                //light PC5..PC2
                PORTC = 0x3C;
                break;
            case 0x0A:
            case 0x0B:
            case 0x0C:
                //light PC5..PC1
                PORTC = 0x3E;
                break;
            case 0x0D:
            case 0x0E:
            case 0x0F:
                //light PC5..PC0
                PORTC = 0x3F;
                break;
            default:
                break;

        }
    }

    return 1;
}
