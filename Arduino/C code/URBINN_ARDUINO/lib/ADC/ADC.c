/*
* ADC.c
*
* Created: 25-9-2017 13:58:22
* Author: Lucan de Groot
*/

#include "ADC.h"
#include "../UART/USART.h"
#include "../CAN/Canbus.h"
#include "../statemachine.h"
#include <avr/interrupt.h>


static volatile uint16_t ADCReading;


/**
 * \brief initialize the ADC
 *
 *
 * \return void
 */
void init_ADC(){
	// reference voltage is AREF
	// should need and external capacitor at AREF
	ADMUX |= (1 << REFS0);

	// enable the ADC and set 128 prescaler
	// clould move aden to read_adc();
	ADCSRA |= (1 << ADEN) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2) | (1 << ADIE); // enable interrupt

	// disable all digital input on analog pins, this saves some power. And we won't use them. May also make the ADC more accurate
	DIDR0 |= (1 << ADC5D)| (1 << ADC4D) | (1 << ADC3D) | (1 << ADC2D) | (1 << ADC1D) | (1 << ADC0D);
}

/**
 * \brief Returns the converted value from the analog pin, returns 0 if the pin isn't analog.
 *
 * \param give the pin number as parameter
 *
 * \return uint16_t ADC value
 */
void read_ADC(uint8_t pin){

	// check if the pin is in the desired range
	if(pin < 0 || pin > 6){
		return 0;
	}

	SMCR |= (1 << SM0); // reduce noise by putting the atmega328 in 'ADC reduce noise mode'

	ADMUX |= (pin & 7);  // select the correct pin (channel)

	// add (1 <<  ADEN)
	ADCSRA |= (1 << ADSC); // start the conversion

	sei(); // enable interrupts
}

static inline uint16_t ADCGetReading() {
	SMCR &= ~(1 << SM0); // return the 328 to normal operation

	// read the data from the register
	uint8_t low  = ADCL;
	uint8_t high = ADCH;

	// combine the two bytes and send them back
	return (high << 8) | low; // (ADCH << 8) | ADCL;
}

// not sure if this is the correct vector
ISR(ADC_vect) {
	ADCReading = ADCGetReading();
	addState(ST_ADC_DONE); // add adc to the queue
}


void ADCSendMessage() {
	tCAN frame;
	frame.header.rtr = 0;

	//print_string("adcreading:  ");
	//print_int_new_line(ADCReading);

	frame.id = 0x123; // set a random id

	// first byte
	frame.data[0] = (ADCReading >> 8); // msb
	// second byte
	frame.data[1] = ADCReading & 0xff; // lsb

	//print_string("ADC reading:  ");
	//print_int_new_line((uint16_t)frame.data);

	// How to convert the data back:
	uint32_t result = frame.data[0] << 8 | frame.data[1];
	print_int_new_line(result);

	// send the message
	//CANTransmitMessage(&frame);
}


	