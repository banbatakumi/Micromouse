#include "mode.hpp"

// #define DEBUG

void Mode::MainMode() {
      processTimer.reset();
      robot->motor.EncoderCompute();
      robot->getSensors();

      LineTrace();

      //  定周期処理
      process_time_ = processTimer.read_us();
      if (process_time_ < PERIOD_US) {
            while (processTimer.read_us() < PERIOD_US);
      } else {
            printf("OverProcess! ");
      }
#ifdef DEBUG
      printf("ProcessTime = %d, LinePosition = %.2lf, MotorL = %.2lf, MotorR = %.2lf\n", process_time_, robot->line.position, robot->motor.encoder.speed_left, robot->motor.encoder.speed_right);
#endif
}