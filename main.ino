#include "c_drivers.h"
#include "peripherals.h"
#include "algebra.h"

float system_data[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

int main() {

  c_setpin(13, true); // LED L
  c_setpin(11, true); // External LED

  c_serial_begin(115200);
  c_init_timer0();
  c_i2c_init();
  init_IMU(imu_250);
  init_servo();
  uint32_t prev_time = c_current_time();
  uint32_t current_time = prev_time;

  while(true) {
    get_IMU_data(imu_250);

    current_time = c_current_time();
    float dt = float(current_time - prev_time) / 1000.0; // converting to sec

    //*******************************************************************************
    system_data[8] = integral(imu_data[5], system_data[8], dt); // yaw
    system_data[7] = integral(imu_data[4], system_data[7], dt); // pitch
    system_data[6] = integral(imu_data[3], system_data[6], dt); // roll
    //*******************************************************************************
    system_data[5] = integral(imu_data[2] * Gravity, system_data[5], dt); // z_v
    system_data[4] = integral(imu_data[1] * Gravity, system_data[4], dt); // y_v
    system_data[3] = integral(imu_data[0] * Gravity, system_data[3], dt); // x_v
    //******************************************************************************
    system_data[2] = integral(system_data[5], system_data[2], dt);  // z
    system_data[1] = integral(system_data[4], system_data[1], dt);  // y
    system_data[0] = integral(system_data[3], system_data[0], dt);  // x
    //******************************************************************************

    // print every sec
    if (current_time / 1000 != prev_time / 1000){
      c_serial_write("Yaw angle:", true);
      c_serial_write_float(system_data[8], true);
      c_serial_write("Pitch:", true);
      c_serial_write_float(system_data[7], true);
      c_serial_write("Roll:", true);
      c_serial_write_float(system_data[6], true);
    
      c_serial_write("X :", true);
      c_serial_write_float(imu_data[0], true);
      c_serial_write("Y:", true);
      c_serial_write_float(imu_data[1], true);
      c_serial_write("Roll:", true);
      c_serial_write_float(imu_data[2], true);

      c_serial_write("*****************************************************************", true);
    }
    
    set_servo(system_data[7]); // set Servo to yaw angle

    //*************************************************************
    //Led L section
    if(system_data[3] > 85 || system_data[3] < -85)
      c_digital_write(13, true);
    else
      c_digital_write(13, false);

    //*************************************************************
    // External Led Section
    if (fabs(imu_data[0] > 1.08)) // External Led 100 percent
      c_pwm_11(255);
    else if (fabs(imu_data[0]) > 0.08)
      c_pwm_11( (fabs(imu_data[0]) - 0.08) * 255);
    else
      c_pwm_11(0); // Turn off External Led
    //*************************************************************

    prev_time = current_time;

    c_delay_milli(100);
  }



  return 0;
}
