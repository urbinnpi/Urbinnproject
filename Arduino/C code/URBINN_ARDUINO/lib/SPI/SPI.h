/*
 * SPI.h
 *
 * Created: 2-5-2018 14:13:24
 *  Author: lucan
 */


#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>

#define F_CPU 16000000UL
#define	P_MOSI	B,3
#define	P_MISO	B,4
#define	P_SCK	B,5


void spi_init_master();
uint8_t spi_putc(uint8_t data);


#endif /* SPI_H_ */