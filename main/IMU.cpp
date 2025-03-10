#include "HardwareSerial.h"
#include "peripherals.h"
#include "algebra.h"


float imu_data[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};  // initialize to 0
 

void init_IMU(IMU_SETTING setting){
  c_i2c_start();
  c_i2c_write(IMU_ADDR << 1 | 0); // Write address of IMU ( `7 bit address` + `0` )
  c_i2c_write(IMU_PWR_REG);
  c_i2c_write(setting); // Starting imu with default mode | refere to docs for other modes
  c_i2c_stop();
}

void get_one_round_IMU_data() {

  
  uint8_t data[14]; // I2C response buffer

  c_i2c_start();
  c_i2c_write(IMU_ADDR << 1 | 0); // Write address of IMU ( `7 bit address` + `0` )
  c_i2c_write(IMU_X_ACCEL_REG);
  c_i2c_stop();

  c_i2c_start();
  c_i2c_write(IMU_ADDR << 1 | 1); // Read address of IMU ( `7 bit address` + `1` )
  // read 14 consecutive registers
  for(uint8_t i=0; i < 13; i++)
    data[i] = c_i2c_read_ack();
  data[13] = c_i2c_read_nack();


  // TODO
  // Modify it based on the setting
  imu_data[6] = ( ((int16_t)data[0] << 8) | data[1] ) / ACCEL_SCALE; // x
  imu_data[7] = ( ((int16_t)data[2] << 8) | data[3] ) / ACCEL_SCALE; // y
  imu_data[8] = ( ((int16_t)data[4] << 8) | data[5] ) / ACCEL_SCALE; // z
  imu_data[9] = ( ((int16_t)data[8] << 8) | data[9] ) / GYRO_SCALE;    // roll
  imu_data[10] = ( ((int16_t)data[10] << 8) | data[11] ) / GYRO_SCALE;  // pitch
  imu_data[11] = ( ((int16_t)data[12] << 8) | data[13] ) / GYRO_SCALE;  // yaw

}


// TODO
// Check the stop ones
void get_IMU_data(IMU_SETTING setting){

  uint16_t times = 100;

  // first one
  get_one_round_IMU_data();
  imu_data[0] = imu_data[6]; // x
  imu_data[1] = imu_data[7]; // y
  imu_data[2] = imu_data[8]; // z
  imu_data[3] = imu_data[9]; // roll
  imu_data[4] = imu_data[10]; // pitch
  imu_data[5] = imu_data[11]; // yaw

  // count time
  for(int i=1; i < times; i++) {
    get_one_round_IMU_data();
    imu_data[0] = ( float(i-1)/float(i) ) * imu_data[0] + imu_data[6] / i;  // x 
    imu_data[1] = ( float(i-1)/float(i) ) * imu_data[1] + imu_data[7] / i;  // y
    imu_data[2] = ( float(i-1)/float(i) ) * imu_data[2] + imu_data[8] / i;  // z
    imu_data[3] = ( float(i-1)/float(i) ) * imu_data[3] + imu_data[9] / i;  // roll
    imu_data[4] = ( float(i-1)/float(i) ) * imu_data[4] + imu_data[10] / i; // pitch
    imu_data[5] = ( float(i-1)/float(i) ) * imu_data[5] + imu_data[11] / i; // yaw
  }


  // romoving noise
  if ( fabs(imu_data[3]) < DEAD_ZONE ) 
    imu_data[3] = 0;

  
  // romoving noise
  if ( fabs(imu_data[4]) < DEAD_ZONE ) 
    imu_data[4] = 0;

  
  // romoving noise
  if ( fabs(imu_data[5]) < DEAD_ZONE ) 
    imu_data[5] = 0;



}



