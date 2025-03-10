/*
 * c_delay.c
 *
 * Created: 2/5/2025 1:25:08 PM
 *  Author: amir
 */ 

#include "c_drivers.h"

volatile unsigned long system_time = 0;  // Variable to hold the number of timer overflows


uint64_t c_current_time(){

  return system_time;

}

// Timer 0 Interrupt Service Routine (ISR)
ISR(TIMER0_COMPA_vect) {
	system_time++;  // Increment the count every time Timer 0 matches OCR0A
}


void c_init_timer0(){
  
	c_clear_interrupts();
	c_set_enable_interrputs();

	// Set Timer 0 to CTC mode
	TCCR0A = 0;               // Normal mode (no PWM, no special behavior)
	TCCR0B = (1 << WGM02) | (1 << CS01) | (1 << CS00);  // CTC mode, Compare mode, prescaler 64 (4 Micro Sec)

	OCR0A = 249;  // Set OCR0A for a 1ms delay (with prescaler 64, the timer will overflow every 1ms)

	TIMSK0 |= (1 << OCIE0A);  // Enable interrupt on compare match A (when timer reaches OCR0A)
}

// Custom delay function using Timer 0 (milli second)
void c_delay_milli(unsigned long ms) {

  //uint64_t start_time = system_time;

	unsigned long target_count = system_time + ms;  // Calculate when to stop (target count)
	
	// Wait until the timer_count reaches the target_count
	while (system_time < target_count);

}

// Custom delay function using Timer 0 (micro second)
// It can have till 3 Micro Second error
//-------------------------------------------------------------------------------------
// Might need to change to timer 0
// void c_delay_micro(unsigned long us) {
  
//   TCCR0A = 0;  // Normal Mode
//   TCCR0B = (1 << CS11); // Prescaler 8 (1 tick = 0.5µs)
  
//   TCNT0 = 0;  // Reset counter
//   uint16_t target = us * 2; // Since 1 tick = 0.5µs, we need 2 ticks per µs
  
//   while (TCNT0 < target);  // Wait for the counter to reach the delay


//   TIMSK0 &= ~(1 << OCIE0A);
// 	TCCR0A = 0;   // Clear TCCR0A register
// 	TCCR0B = 0;   // Clear TCCR0B register
	
// 	timer_count = 0;
// }