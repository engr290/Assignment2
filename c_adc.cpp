
/*
 * c_adc.c
 *
 * Created: 1/30/2025 3:49:43 PM
 *  Author: amir
 */ 

#include "./c_drivers.h"

bool c_set_adc_reference(c_ADC_ref reference) {

	// Selecting ADC reference (REFS1 and REFS0 are bits 7 and 6)
	ADMUX = (ADMUX & 0x3F);  // reset REFS1 and REFS0 to 0
	switch (reference) {
		case c_VCC:
			ADMUX |= (1 << REFS0);  // REFS1 = 0, REFS0 = 1
			break;
		case c_AREF:
			// REFS1 = 0, REFS0 = 0
      ADMUX &= ~( (1 << REFS0) || (1 << REFS1) ) ;
			break;
		case c_internal_1_1:
			ADMUX |= (1 << REFS1) | (1 << REFS0);  // REFS1 = 1, REFS0 = 1
			break;
		default:
			return false;
	}

	// Set ADC prescaler to 128 (for 16 MHz -> ADC clock = 125 kHz)
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

	return true;
}

bool c_set_adc_pin(uint8_t pin) {
	if(pin > 7)
		return false;
		
	ADMUX = (ADMUX & 0xF0) | (pin & 0x07);
	return true;
}

uint16_t c_analog_read(){

	ADCSRA |= (1 << ADSC);   // start reading

	// i is there for timeout
	for(int i = 0; i < 10000 && (ADCSRA & (1 << ADSC)); i++);
	
	return ADC;

}
