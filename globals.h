
#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL

// IMU
#define IMU_ADDR  0x68  // 7 bit address
#define IMU_WHO_AM_I 0x0
#define IMU_PWR_REG 0x6B
#define IMU_X_ACCEL_REG 0x3B // It is the x acceleration and rest of the registers are increamentally after it
#define IMU_GYTO_X 0x43
#define DEAD_ZONE 1.0


// struct system{
//   uint16_t yaw_angle;
//   uint16_t accel_x;
//   uint16_t accel_y;
//   uint16_t accel_z;
// };


extern float imu_data[12];
extern float system_data[9];

#endif