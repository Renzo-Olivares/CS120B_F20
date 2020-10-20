/*	Author: roliv006
 *  Partner(s) Name: 
 *	Lab Section: 22
 *	Assignment: Lab #2  Exercise #3
 *	Exercise Description: Extend the previous program to still write the available spaces number, but only to
 *  PC3..PC0, and to set PC7 to 1 if the lot is full.
 *  
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{START, OUTPUT}state;

void Tick(){
    unsigned char pinA0 = PINA & 0x01;
    unsigned char pinA1 = (PINA & 0x02) >> 1;
    unsigned char pinA2 = (PINA & 0x04) >> 2;
    unsigned char pinA3 = (PINA & 0x08) >> 3;
    unsigned char availcnt = pinA0 + pinA1 + pinA2 + pinA3;
    unsigned char fulllots = pinA0 & pinA1 & pinA2 & pinA3;

   switch(state){
      case START:
         state = OUTPUT;
         break;
      case OUTPUT:
         break;
      default:
         break;
   }
   switch(state){
      case START:
         break;
      case OUTPUT:
         PORTC = (fulllots << 8) & availcnt;
         break;
      default:
         break;
   }
}

int main(void) {
    DDRA = 0x00;
    PORTA = 0xFF;
    DDRC = 0xFF;
    PORTC = 0x00;

    state = START;

    while(1){
        Tick();
    }

    return 1;
}
