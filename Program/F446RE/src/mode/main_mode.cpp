#include "main_mode.hpp"

// #define DEBUG

MainMode::MainMode() {
}
float p, i, d, pid, pre_p;

void MainMode::loop() {
      processTimer.reset();
      robot.motor.EncoderCompute();
      robot.getSensors();

      const float Kp = 2.5, Ki = 1, Kd = 0.02;
      int16_t left, right;
      p = robot.line.position - 0;
      i += p * processTime * 0.000001f;
      d = (p - pre_p) / (processTime * 0.000001f);
      pre_p = p;
      pid = p * Kp + i * Ki + d * Kd;
      if (abs(p) < 1) i = 0.5;
      left = pid * 2;
      right = pid * -2;
      if (abs(left) > 200) left = 200 * (abs(left) / left);
      if (abs(right) > 200) right = 200 * (abs(right) / right);
      if (abs(robot.line.position) < 5) {
            left += 120;
            right += 120;
      } else {
            left += 60;
            right += 60;
      }
      if (abs(left) > 300) left = 300 * (abs(left) / left);
      if (abs(right) > 300) right = 300 * (abs(right) / right);
      // robot.motor.Drive(20, 20);
      // printf("left = %d, right = %d\n", left, right);

      //  定周期処理
      processTime = processTimer.read_us();
      if (processTime < PERIOD_US) {
            while (processTimer.read_us() < PERIOD_US);
      } else {
            printf("OverProcess! ");
      }
#ifdef DEBUG
      printf("ProcessTime = %d, LinePosition = %.2lf, MotorL = %.2lf, MotorR = %.2lf\n", processTime, robot.line.position, robot.motor.encoder.speed_left, robot.motor.encoder.speed_right);
#endif
}