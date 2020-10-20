/*	Author: roliv006
 *  Partner(s) Name: 
 *	Lab Section: 22
 *	Assignment: Lab #2  Exercise #2
 *	Exercise Description: Port A's pins 3 to 0, each connect to a parking space sensor, 1 meaning
 *  a car is parked in the space, of a four space parking lot. Write a program" that outputs in
 *  binary on Port C the number of available spaces (Hint: declare a variable "unsigned char cntavail;"
 *  you can assign a number to a port as follows: PORTC = cntavail;).
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
    unsigned char pinA1 = PINA & 0x02;
    unsigned char pinA2 = PINA & 0x04;
    unsigned char pinA3 = PINA & 0x08;
    unsigned char availcnt = pinA0 + pinA1 + pinA2 + pinA3;

   switch(state){
      case START:
         state = OUTPUT;
         printf("start transition\n");
         break;
      case OUTPUT:
         printf("out transition\n");
         break;
      default:
         printf("error transition\n");
         break;
   }
   switch(state){
      case START:
         printf("start state\n");
         break;
      case OUTPUT:
         PORTC = availcnt;
         printf("out state\n");
         break;
      default:
         printf("error state\n");
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
