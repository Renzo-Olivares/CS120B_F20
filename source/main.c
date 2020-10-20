/*	Author: roliv006
 *      Partner(s) Name: 
 *	Lab Section: 22
 *	Assignment: Lab #3  Exercise #3
 *	Exercise Description: In addition to the above, PA4 is 1 if a key is in the ignition, PA5 is one if a driver is seated, and PA6
 *  is 1 if the driver's seatbelt is fastened. PC7 should light a "Fasten seatbelt" icon if a key is in the ignition, there driver is
 *  seated, but the belt is not fastened.
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
        unsigned char pinA4 = PINA & 0x10;
        unsigned char pinA5 = PINA & 0x20;
        unsigned char pinA6 = PINA & 0x40;

        unsigned char fuellevel = pinA0 + pinA1 + pinA2 + pinA3;
        unsigned char fastenwarning = (pinA4 && pinA5) && !pinA6;

        switch(fuellevel){
            case 0x01:
            case 0x02:
                //light PC5
                //light low fuel PC6
                PORTC = fastenwarning? 0xE0: 0x60;
                break;
            case 0x03:
            case 0x04:
                //light PC5 and PC4
                //light low fuel PC6
                PORTC = fastenwarning? 0xF0:0x70;
                break;
            case 0x05:
            case 0x06:
                //light PC5..PC3
                PORTC = fastenwarning? 0xB8:0x38;
                break;
            case 0x07:
            case 0x08:
            case 0x09:
                //light PC5..PC2
                PORTC = fastenwarning? 0xBC:0x3C;
                break;
            case 0x0A:
            case 0x0B:
            case 0x0C:
                //light PC5..PC1
                PORTC = fastenwarning? 0xBE:0x3E;
                break;
            case 0x0D:
            case 0x0E:
            case 0x0F:
                //light PC5..PC0
                PORTC = fastenwarning? 0xBF:0x3F;
                break;
            default:
                break;

        }
    }

    return 1;
}
