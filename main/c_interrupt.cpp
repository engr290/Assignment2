/*
 * c_interrupt.c
 *
 * Created: 2/5/2025 2:08:25 PM
 *  Author: amir
 */ 


#include "c_drivers.h"

void c_clear_interrupts() {
	SREG &= ~(1 << 7);  // Clear I-bit (disable global interrupts)
} 


void c_set_enable_interrputs() {
	SREG |= (1 << 7);  // Set I-bit (enable global interrupts)
}