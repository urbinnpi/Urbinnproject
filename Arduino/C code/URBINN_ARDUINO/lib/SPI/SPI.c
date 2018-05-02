/*
 * SPI.c
 *
 * Created: 2-5-2018 14:13:15
 *  Author: lucan
 */
#include "SPI.h"

#include "avr/io.h"

//Initialize SPI Master Device
void spi_init_master() {
	DDRB |= (1<<5)|(1<<3);              //Set MOSI, SCK as Output
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0); //Enable SPI, Set as Master
	//Prescaler: Fosc/16, Enable Interrupts
}

//Function to send and receive data
uint8_t spi_putc( uint8_t data ) {
	SPDR = data;                       //Load data into the buffer
	while(!(SPSR & (1<<SPIF) ));       //Wait until transmission complete
	return(SPDR);                      //Return received data
}