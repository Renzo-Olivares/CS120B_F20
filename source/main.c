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

enum States{START, COUNT, ONE, TWO, THREE, FOUR, OUTPUT}state;
unsigned char availcnt = 0x00;
unsigned char pastSensor = 0x00;

void Tick(){
    unsigned char pinA0 = PINA && 0x01;
    unsigned char pinA1 = PINA && 0x02;
    unsigned char pinA2 = PINA && 0x04;
    unsigned char pinA3 = PINA && 0x08;

   switch(state){
      case START:
         state = COUNT;
         printf("start transition\n");
         break;
      case COUNT:
         state = !pinA0 && !pinA1 && !pinA2 && !pinA3? OUTPUT: ONE;
         printf("count transition\n");
         break;
      case ONE:
         state = pinA1 || pinA2 || pinA3? TWO: OUTPUT;
         printf("one transition\n");
         break;
      case TWO:
         state = pinA1 || pinA2? THREE: OUTPUT;
         printf("two transition\n");
         break;
      case THREE:
         state = pinA2? FOUR: OUTPUT;
         printf("three transition\n");
         break;
      case FOUR:
         state = OUTPUT;
         printf("four transition\n");
         break;
      case OUTPUT:
         printf("out transition\n");
         state = pastSensor != (pinA0 + pinA1 + pinA2 + pinA3)? COUNT: OUTPUT;
         break;
      default:
         printf("error transition\n");
         break;
   }
   switch(state){
      case START:
         printf("start state\n");
         break;
      case COUNT:
         PORTC = 0x00;
         availcnt = 0x00;
         pastSensor = 0x00;
         printf("count state\n");
         break;
      case ONE:
         if(pinA0){
            availcnt++;
         }
         printf("one state\n");
         break;
      case TWO:
         if(pinA1){
            availcnt++;
         }
         printf("two sttae\n");
         break;
      case THREE:
         if(pinA2){
            availcnt++;
         }
         printf("three state\n");
         break;
      case FOUR:
         if(pinA3){
            availcnt++;
         }
         pastSensor = pinA0 + pinA1 + pinA2 + pinA3;
         printf("four state\n");
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
