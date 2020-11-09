/*	Author: roliv006
 *  Partner(s) Name: 
 *	Lab Section: 22
 *	Assignment: Lab #7  Exercise #3
 *	Exercise Description: Design a system where an LED is illuminated only if enough light is
 *  detected from the photo resistor. Criteria:
 *  If the result of the ADC is >= MAX/2, the LED is illuminated.
 *  If the result of the ADC is < MAX/2, the LED is turned off.
 * 
 *  Demo: https://youtu.be/vHK4gLBZXPQ
 * 
 *  MAX = 0010000111 = 0x87 - Shined a flashlight from a close distance counted bits
 *  MIN = 0000111001 = 0x39 - counted bits when covering photoresistor
 * 
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{START, LEDON, LEDOFF}state;

// Value of ADC register is now stored in variable x.
unsigned short x;
const unsigned short MAX = 0x87;
const unsigned short MIN = 0x39;

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
            PORTB = x >= MAX/2 ? 0x01 : 0x00;
            break;
        case LEDON:
            break;
        case LEDOFF:
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