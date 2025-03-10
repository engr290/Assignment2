/*
 * c_drivers.h
 *
 * Created: 1/30/2025 3:49:09 PM
 *  Author: amir
 */ 


#ifndef C_DRIVERS_H_
#define C_DRIVERS_H_

#include "globals.h"
#include <avr/io.h>
#include <avr/interrupt.h>


typedef enum {
	c_VCC,
	c_AREF,
	c_internal_1_1
} c_ADC_ref;

// GPIO
bool c_setpin(uint8_t pin, bool IsOutput);
bool c_digital_read(uint8_t pin);
bool c_digital_write(uint8_t pin, bool setOn);


// ADC
bool c_set_adc_reference(c_ADC_ref reference);
bool c_set_adc_pin(uint8_t pin);
uint16_t c_analog_read();

// time
void c_delay_milli(unsigned long ms);
// void c_delay_micro(unsigned long Ms); // Only used in pulseIn function
uint64_t c_current_time(); // return current time milli sec
void c_init_timer0();


//pwm
void c_pwm_9(uint8_t val);  // Set to higher frequency for servo motor
void c_pwm_11(uint8_t val); // Inverted | connected to the external LED


// For debugging only
// Serial
void c_serial_begin(int boud_rate);
void c_serial_write_char(char c);
void c_serial_write(char* buffer, bool new_line);
void c_serial_write_float(float val, bool new_line)

// Same as sei and cli
// better to used them than these
void c_clear_interrupts();
void c_set_enable_interrputs();


// This section is only used for IMU
// i2c drivers
void c_i2c_init();
void c_i2c_start();
void c_i2c_stop();
void c_i2c_write(uint8_t data);
uint8_t c_i2c_read_ack();
uint8_t c_i2c_read_nack();


void uart_print_int(uint16_t value);

#endif /* C_DRIVERS_H_ */
