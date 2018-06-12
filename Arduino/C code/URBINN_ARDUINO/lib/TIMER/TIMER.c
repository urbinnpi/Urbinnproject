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

	TIMERReInit();

	// 1 Hz
	ICR1 = 6250;

	// overflow interrupt
	TIMSK1 |= (1 << TOIE1);

	sei();
}


void TIMERReInit() {
	// 16 bit fast PWM
	// ICR1 is top /256 prescaler
	TCCR1A |= (1<<WGM11);
	TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS12);
}

void stopTimer() {
	// clear the registers
	TCCR1A = 0x00;
	TCCR1B = 0x00;
}