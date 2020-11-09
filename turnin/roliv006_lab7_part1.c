/*	Author: roliv006
 *  Partner(s) Name: 
 *	Lab Section: 22
 *	Assignment: Lab #7  Exercise #1
 *	Exercise Description: Make sure your breadboard is wired according to the prelab. 
 *  The potentiometer is used to adjust the voltage supplied to the microcontroller for ADC . 
 *  Design a system that reads the 10-bit ADC result from the ADC register, and displays the 
 *  result on a bank of 10 LEDs.
 *
 *  Demo: https://youtu.be/XONinV-tJSw
 * 
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
