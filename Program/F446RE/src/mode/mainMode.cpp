#include "mainMode.hpp"

// #define DEBUG

MainMode::MainMode() {
}
float p, i, d, pid, pre_p;
void MainMode::loop() {
      processTimer.reset();
      robot.motor.EncoderCompute();
      robot.getSensors();

      const float Kp = 2.5, Ki = 1, Kd = 0.05;
      int16_t left, right;
      p = robot.line.position - 0;
      i += p * processTime * 0.000001f;
      d = (p - pre_p) / (processTime * 0.000001f);
      pre_p = p;
      pid = p * Kp + i * Ki + d * Kd;
      if (abs(p) < 1) i = 0.5;
      left = pid * 2;
      right = pid * -2;
      if (abs(left) > 250) left = 250 * (abs(left) / left);
      if (abs(right) > 250) right = 250 * (abs(right) / right);
      if (abs(robot.line.position) < 5) {
            left += 150;
            right += 150;
      } else {
            left += 100;
            right += 100;
      }
      if (abs(left) > 500) left = 500 * (abs(left) / left);
      if (abs(right) > 500) right = 500 * (abs(right) / right);
      robot.motor.Drive(left, right);
      // for (uint8_t i = 0; i < 10; i++) printf("%d, ", robot.line.mainVal[i]);
      // printf("\n");
      // 定周期処理
      processTime = processTimer.read_us();
      if (processTime < PERIOD_US) {
            while (processTimer.read_us() < PERIOD_US);
#ifdef DEBUG
            printf("ProcessTime = %d, LinePosition = %f\n", processTime, robot.line.position);
#endif
      } else {
            printf("OverProcess! ");
      }
}