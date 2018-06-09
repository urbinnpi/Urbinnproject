#include "TIMER.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include "../stateMachine.h"


ISR(TIMER1_OVF_vect) {
	// poll sensors that don't interrupt
	addState(ST_POLL_SENSOR);
}


void TIMER_init() {
	print_string_new_line("Starting timer");
	cli();

	// clear the registers
	TCCR1A = 0x00;
	TCCR1B = 0x00;

	// 16 bit fast PWM
	// ICR1 is top /8 prescaler
	TCCR1A |= (1<<WGM11);
	TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS11);

	// overflow interrupt
	TIMSK1 |= (1 << TOIE1);

	// Top is 40K => 50Hz or 20ms period
	ICR1 = 40000;

	sei();
}


void TIMERReInit() {
	// 16 bit fast PWM
	// ICR1 is top /8 prescaler
	TCCR1A |= (1<<WGM11);
	TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS11);
}

void stopTimer() {
	// clear the registers
	TCCR1A = 0x00;
	TCCR1B = 0x00;
}