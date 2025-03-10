

#include "algebra.h"


int16_t integral(int16_t y, int16_t c, float dt){
  return c + y * dt;
}

// Absolute
float fabs(float num) {
  
  if(num < 0)
    return -num;

  return num;
}


int16_t fabs(int16_t num) {

  if(num < 0)
    return -num;

  return num;
}