

#ifndef ALGEBRA_H_
#define ALGEBRA_H_

#include <avr/io.h>
#include <avr/interrupt.h>

int16_t integral(int16_t y, int16_t c, float dt);

float fabs(float num);

int16_t fabs(int16_t num);

#endif