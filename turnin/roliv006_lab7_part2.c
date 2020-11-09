/*	Author: roliv006
 *  Partner(s) Name: 
 *	Lab Section: 22
 *	Assignment: Lab #7  Exercise #2
 *	Exercise Description: Revise exercise 1 by replacing the potentiometer with a photoresistor and 330 
 *  ohm resistor. Take note of the highest ADC value displayed (MAX) when the photoresistor is
 *  exposed to light, and the lowest ADC value displayed (MIN) when the photoresistor is deprived 
 *  of all light. These values will be used for the remaining lab exercises.
 *
 *  Demo: https://youtu.be/0vWQcA-VyyA
 * 
 *  MAX = 0010000111 = 0x87 - Shined a flashlight from a close distance counted bits
 *  MIN = 0000111001 = 0x39 - counted bits when covering photoresistor
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{START}state;

// Value of ADC register is now stored in variable x.
unsigned short x;
unsigned char lower;
unsigned char upper;

void ADC_init() {
    ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
    // ADEN: setting this bit enables analog-to-digital conversion.
    // ADSC: setting this bit starts the first conversion.
    // ADATE: setting this bit enables auto-triggering. Since we are in Free Running Mode,
    //        a new conversion will trigger whenever the previous conversion completes.
}

void Tick() {
    x = ADC;

    switch(state){
        case START:
            lower = (char)(x & 0x00FF);
            upper = (char)(x >> 8);
            PORTB = lower;
            PORTD = upper;
            break;
        default:
            break;
    }
}

int main(void) {
    DDRB = 0xFF; // Set port B to output
    DDRD = 0xFF;
    DDRA = 0x00;
    PORTB = 0x00; // Init port B to 0s
    PORTD = 0x00;
    PORTA = 0xFF;

    state = START;

    ADC_init();

    /* Insert your solution below */
    while (1) {
        Tick();
    }
    return 1;
}
