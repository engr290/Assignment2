#include "HardwareSerial.h"

#include "peripherals.h"


void init_servo(){
  DDRB |= (1 << PB1); // Set PB1 (OC1A) as output for PWM
  TCCR1A = (1 << WGM11) | (1 << COM1A1); // Fast PWM, non-inverting mode
  TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11); // Prescaler = 8
  ICR1 = 39999; // Set TOP for 50Hz PWM frequency
  OCR1A = 3000; // Initialize to center position (1.5ms pulse width)
}


void set_servo(uint16_t angle){

  angle += 90;

  if (angle < 0) angle = 0;
  if (angle > 180) angle = 180;

  int angle_adjust = 200;

  switch(angle) {
      case 0:
          angle_adjust = -angle_adjust; // Missing semicolon added
          break;

      case 180:
          angle_adjust = angle_adjust; // Semicolon is already correct
          break;

      default: // Optional but recommended for completeness
          angle_adjust = 0; // Handle unexpected values
          break;
  }

  uint16_t pulseWidth = ((uint32_t)angle * (2400 - 600) / 180) + 600 + angle_adjust;
  
  // Convert pulse width to timer counts (each count is 0.5us with prescaler of 8)
   OCR1A = pulseWidth * 2; // Set the timer compare value
  
  //OCR1A = ( angle / 180 + 0.5 ) * 4000 ; // Set the timer compare value

}


