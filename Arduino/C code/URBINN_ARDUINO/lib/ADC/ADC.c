/*
* ADC.c
*
* Created: 25-9-2017 13:58:22
* Author: Lucan de Groot
*/

#include "ADC.h"


/**
 * \brief initialize the ADC
 *
 *
 * \return void
 */
void init_ADC(){
	// reference voltage is AREF
	ADMUX |= (1 << REFS0);

	// enable the ADC and set 128 prescaler
	ADCSRA |= (1 << ADEN) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);

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
extern inline uint16_t read_ADC(uint8_t pin){

	// check if the pin is in the desired range
	if(pin < 0 || pin > 6){
		return 0;
	}

	uint8_t low, high; // used to read the result from the registers

	SMCR |= (1 << SM0); // reduce noise by putting the atmega328 in 'ADC reduce noise mode'

	ADMUX |=  (pin & 7);  // select the correct pin (channel)

	ADCSRA |= (1 << ADSC); // start the conversion

	// ADSC is cleared when the conversion finishes
	while (bit_is_set(ADCSRA, ADSC)); // wait for the conversation to finish

	SMCR |= (0 << SM0); // return the 328 to normal operation

	// read the data from the register
	low  = ADCL;
	high = ADCH;

	// combine the two bytes and send them back
	return (high << 8) | low;
}