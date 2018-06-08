/*
* ADC.h
*
* Created: 25-9-2017 13:58:05
* Author: Lucan de Groot
*/


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
#include <stdint.h>

void init_ADC();
inline uint16_t read_ADC(uint8_t);


#endif /* ADC_H_ */