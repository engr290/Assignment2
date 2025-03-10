#include "c_drivers.h"
#include "peripherals.h"
#include "algebra.h"

float system_data[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

int main() {


  c_setpin(13, true);
  Serial.begin(115200);
  c_init_timer0();
  c_i2c_init();
  init_IMU(imu_250);
  init_servo();
  uint32_t prev_time = c_current_time();
  uint32_t current_time = prev_time;


  while(true) {
    get_IMU_data(imu_2000);

    current_time = c_current_time();
    float dt = float(current_time - prev_time) / 1000.0;

    //*******************************************************************************
    system_data[8] = integral(imu_data[5], system_data[8], dt); // yaw
    system_data[7] = integral(imu_data[4], system_data[7], dt); // pitch
    system_data[6] = integral(imu_data[3], system_data[6], dt); // roll
    //*******************************************************************************
    system_data[5] = integral(imu_data[2], system_data[5], dt); // z_v
    system_data[4] = integral(imu_data[1], system_data[4], dt); // y_v
    system_data[3] = integral(imu_data[0], system_data[3], dt); // x_v
    //******************************************************************************
    system_data[2] = integral(system_data[5], system_data[2], dt);  // z
    system_data[1] = integral(system_data[4], system_data[1], dt);  // y
    system_data[0] = integral(system_data[3], system_data[0], dt);  // x
    //******************************************************************************


    // Serial.println("Yaw angle:");
    // Serial.println(system_data[8]);
    // Serial.println("Pitch:");
    // Serial.println(system_data[7]);
    // Serial.println("Roll:");
    // Serial.println(system_data[6]);
    
    Serial.println("X :");
    Serial.println(imu_data[0]);
    // Serial.println("Y:");
    // Serial.println(imu_data[1]);
    // Serial.println("Roll:");
    // Serial.println(imu_data[2]);

    Serial.println("*****************************************************************");

    Serial.println("X:");
    Serial.println(system_data[0]);
    
    set_servo(system_data[7]);

    if(system_data[3] > 85 || system_data[3] < -85)
      c_digital_write(13, true);
    else
      c_digital_write(13, false);

    if (fabs(imu_data[0] > 1.08))
      c_pwm_11(255);

    if (fabs(imu_data[0]) > 0.08)
      c_pwm_11( (fabs(imu_data[0]) - 0.08) * 255);
    
    c_pwm_11(0);

    prev_time = current_time;

    c_delay_milli(1000);
  }



  return 0;
}
