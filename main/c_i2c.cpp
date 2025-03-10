
#include "c_drivers.h"

// IMPORTANT!!!!
// ALL the todos indicate infinite loop


void c_i2c_init() {
  TWSR = 0x00;  // Set prescaler to 1
  TWBR = 12;    // Set SCL frequency to 400kHz assuming F_CPU = 16MHz
}

// TODO
void c_i2c_start() {
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
  for (int i=0; i < 10000 && !(TWCR & (1 << TWINT)); i++);
}


// TODO
void c_i2c_stop() {
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
  for (int i=0; i < 10000 && TWCR & (1 << TWSTO); i++);
}

// TODO
void c_i2c_write(uint8_t data) {
  TWDR = data;
  TWCR = (1 << TWINT) | (1 << TWEN);
  for (int i=0; i< 10000 && !(TWCR & (1 << TWINT)); i++);
}

//TODO
uint8_t c_i2c_read_ack() {
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
  for (int i=0; i < 10000 && !(TWCR & (1 << TWINT)); i++);
  return TWDR;
}

//TODO
uint8_t c_i2c_read_nack() {
  TWCR = (1 << TWINT) | (1 << TWEN);
  for (int i=0; i < 10000 && !(TWCR & (1 << TWINT)); i++);
  return TWDR;
}