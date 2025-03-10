/*
 * c_gpio.c
 *
 * Created: 1/30/2025 3:49:28 PM
 *  Author: amir
 */ 

#include "./c_drivers.h"


bool c_setpin(uint8_t pin, bool IsOutput){
  uint8_t temp;
	if (pin < 8){
    if (IsOutput)
		  DDRD |= (1 << pin);
    else
      DDRD &= ~(1 << pin);
	}
	else if (pin < 14){
		pin -= 8;
    if (IsOutput)
		  DDRB |= (1 << pin);
    else
      DDRB &= ~(1 << pin);
	}
	else
		return false;

	return true;
}

bool c_digital_read(uint8_t pin){

  if(pin < 8){
    return PIND & (1 << pin);
  }
  else if(pin < 14) {
    return PINB & (1 << (pin - 8));
  }

  return false;
}

bool c_digital_write(uint8_t pin, bool setOn){

	if (pin < 8){
		uint8_t bit_val = (1 << pin);
		if (setOn)
			PORTD |= bit_val;
		else
			PORTD &= ~bit_val;
	}
	else if (pin < 14){
		pin -= 8;
		uint8_t bit_val = (1 << pin);
		if (setOn)
			PORTB |= bit_val;
		else
			PORTB &= ~bit_val;
	}
	else
		return false;

	return true;

}


void c_pwm_9(uint8_t val) {
  DDRB |= (1 << PB1); // Set PB1 (OC1A) as output for PWM
  TCCR1A = (1 << WGM11) | (1 << COM1A1); // Fast PWM, non-inverting mode
  TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11); // Prescaler = 8
  ICR1 = 39999; // Set TOP for 50Hz PWM frequency
  OCR1A = 0; // Initialize to center position (1.5ms pulse width)
}


// Sends an inverted pwm
void c_pwm_11(uint8_t val) {


  val = 255 - val; // Pin 11 is inverted

    // Configure Timer2 for Fast PWM, non-inverting mode
  TCCR2A = (1 << WGM20) | (1 << WGM21) | (1 << COM2A1); // Fast PWM mode, non-inverting
  TCCR2B = (1 << CS21); // Prescaler = 8 → PWM frequency ~8kHz

  OCR2A = val; // Set 50% duty cycle (0-255)
}