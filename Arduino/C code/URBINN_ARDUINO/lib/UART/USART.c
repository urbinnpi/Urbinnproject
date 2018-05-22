/*
* communication_interface.c
*
* Created: 21-9-2017 10:55:31
* Author: Lucan de Groot
*/

#include "USART.h"
#include "../CAN/Canbus.h"
#include <avr/interrupt.h>
#include <string.h> // for memset
#include "../common.h"

volatile char receiveBuffer[RECEIVE_BUFFER_MAX_SIZE];		// receive buffer
volatile uint8_t receiveBufferCounter;						// counter
volatile uint8_t messageReceived;

/**
 * \brief initialize the USART
 *
 * \param baudrate the baudrate the USART will run on
 *
 * \return void
 */
void USART_init(uint32_t baudrate){

	// calculate the baudrate, see the datasheet for more information
	uint16_t baud_setting = (F_CPU / 8 / baudrate - 1) ;

	// assign the baud_setting
	UBRR0H = baud_setting >> 8;
	UBRR0L = baud_setting;

	// set double data speed
	UCSR0A = (1<<U2X0);

	// enable TX and RX (RX is not necessary)
	UCSR0B |= _BV(RXEN0) | _BV(TXEN0) | _BV(RXCIE0);

	// 8 bit data, 1 stop, no parity
	UCSR0C |= _BV(UCSZ01) | _BV(UCSZ00);


	// confirm the init
	print_string_new_line("USART INIT DONE");

	sei(); // enable interrupt
}

ISR(USART_RX_vect) {
	receiveBuffer[receiveBufferCounter] = UDR0;
	receiveBufferCounter++;

	// check for full message or max Can size
	if (receiveBuffer[receiveBufferCounter-1] != '\r') {
		addState(ST_READ_UART);
	}
}

void clearBuffer() {
	receiveBufferCounter = 0;
	memset((char*)receiveBuffer, 0 , RECEIVE_BUFFER_MAX_SIZE);
}

void receive () {
	print_string("Received data: ");
	print_string_new_line((char*)receiveBuffer);
	print_string("Counter: ");
	print_int_new_line(receiveBufferCounter);

	tCAN frame;
	frame.header.rtr = 0;
	frame.id = 0x631;

	// loop for every full message
	uint8_t i = 0;
	for (i = 0; i + CAN_MAX_LENGTH <= receiveBufferCounter; i += CAN_MAX_LENGTH) {
		// copy one frame into the frame
		memcpy(frame.data, &receiveBuffer[i], CAN_MAX_LENGTH);

		// set the length
		frame.header.length = CAN_MAX_LENGTH;

		// send the frame
		message_tx(&frame);
		print_string_new_line((char*)frame.data);
	}

	// clean the dataframe
	memset(frame.data, 0, (size_t)CAN_MAX_LENGTH);

	// put the leftovers in the last frame
	uint8_t j = 0;
	for (; receiveBuffer[i] != '\r'; i++) {
		frame.data[j] = receiveBuffer[i];
		j++;
	}

	// set the correct length and send the frame;
	frame.header.length = j;
	message_tx(&frame);
	print_string_new_line((char*)frame.data);

	// clean the receive buffer
	clearBuffer();
}


/**
 * \brief this function transmits one char of data via the USART
 *
 * \param data char that needs to be send
 *
 * \return void
 */
void USART_transmit(const char * data){

	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) )
	;

	/* Put data into buffer, sends the data */
	UDR0 = *data;

}

void print_int(int32_t data) {
	char data_buffer[(int)(log(data)+2)]; // size of the number (log(number)+1) + 1 for the /0

	itoa(data, data_buffer, 10); // convert the int to string, base 10

	// print the newly created string
	print_string(data_buffer);
}

void print_int_new_line(int32_t data) {
	print_int(data);

	print_new_line();
}

void print_string(char * data) {

	// transmit the data char by char
	for(; *data != '\0'; data++){
		USART_transmit(data);
	}
}

void print_string_new_line(char * data) {
	print_string(data);

	print_new_line();
}

/**
 * \brief This function prints a new line
 *
 *
 * \return void
 */
void print_new_line(){
	print_string("\r\n\0");
}

/**
 * \brief plot two values in 'Serial Port Plotter'
 *
 * \param first value you want to plot
 * \param Second value you want to plot
 *
 * \return void
 */
void plot2(uint32_t val1, uint32_t val2){
	USART_transmit("$");
	print_int(val1);
	USART_transmit(" ");
	print_int(val2);
	USART_transmit(";");
}

/**
 * \brief plot one value in 'Serial Port Plotter'
 *
 * \param value you want to plot
 *
 * \return void
 */
void plot1(uint32_t val){
	USART_transmit("$");
	print_int(val);
	USART_transmit(";");
}