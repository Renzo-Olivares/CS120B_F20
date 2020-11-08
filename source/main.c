/*	Author: renzo
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

// TimerISR() sets this to 1. C programmer should clear to 0.
volatile unsigned char TimerFlag = 0;

// Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
unsigned long _avr_timer_M = 1; // Start count from herer, down to 0. Default 1ms.
unsigned long _avr_time_cntcurr = 0; //Current internal count of 1ms ticks

void TimerOn() {
    // AVR timer/counter controller register TCCR1
    TCCR1B = 0x0B; // bit3 = 0: CTC mode (clear timer on compare)
                   // bit2bit1bit0=011: pre-scaler /64
                   // 00001011: 0x0B
                   // SO, 8 MHz clock or 8,000,000 /64 = 125,000 ticks/s
                   // Thus, TCNT1 register will count at 125,000 ticks/s

    OCR1A = 125;

    TIMSK1 = 0x02;

    TCNT1 = 0;

    _avr_time_cntcurr = _avr_timer_M;

    SREG |= 0x80;
}

void TimerOff() {
    TCCR1B = 0x00;
}

void TimerISR() {
    TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect) {
    _avr_timer_cntcurr--;
    if (_avr_timer_cntcurr == 0){
        TimerISR();
        _avr_timer_cntcurr = _avr_timer_M;
    } 
}

void TimerSet(unsigned long M) {
    _avr_timer_M = M;
    _avr_timer_cntcurr = _avr_timer_M;
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0xFF;
    PORTB = 0x00;
    TimerSet(1000);
    TimerOn();
    unsigned char tmpB = 0x00;
    /* Insert your solution below */
    while (1) {
        tmpb = -tmpB;
        PORTB = tmpB;
        while(!TimerFlag);
        TimerFlag = 0;
    }
    return 1;
}
