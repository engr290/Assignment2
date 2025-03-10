/*
 * c_usart.c
 *
 * Created: 1/30/2025 3:50:01 PM
 *  Author: amir
 */ 

#include "./c_drivers.h"


void c_serial_begin(int boud_rate) {
	// Setting up boud rate
	uint16_t val = ((F_CPU / (16UL * boud_rate)) - 1);
	UBRR0H = (val >> 8);
	UBRR0L = val;

	UCSR0B = (1 << TXEN0); // Enable transmitter
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8-bit data - no parity - 1 stop bit
}

void c_serial_write_char(char c) {
	while (!(UCSR0A & (1 << UDRE0))); // Wait until UDR0 is empty
	UDR0 = c; // Send data
}


void c_serial_write(char* buffer, int len, bool new_line) {
	for(int i = 0; i < len; i++)
		c_serial_write_char(buffer[i]);

	if (new_line) {
		c_serial_write_char(10);	
	}
}


// void uart_print_int(uint16_t value) {
//     char buffer[10];
//     sprintf(buffer, "%d", value);  // Convert integer to string
//     uart_print(buffer);
// }