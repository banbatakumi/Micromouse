#include "mainMode.hpp"

// #define DEBUG

MainMode::MainMode() {
}

void MainMode::loop() {
      processTimer.reset();
      robot.motor.EncoderCompute();
      robot.getSensors();

      static float p, i, d, pid, pre_p;
      const float Kp = 2, Ki = 0.1, Kd = 0;
      int16_t left, right;
      p = robot.line.position - 0;
      i = p * processTime * 0.000001f;
      d = (pre_p - p) / (processTime * 0.000001f);
      pre_p = p;
      pid = p * Kp + i * Ki + d * Kd;
      left = robot.line.position * 2;
      right = robot.line.position * -2;
      if (abs(left) > 75) left = 75 * (abs(left) / left);
      if (abs(right) > 75) right = 75 * (abs(right) / right);
      if (abs(robot.line.position) < 10) {
            left += 90;
            right += 90;
      } else {
            left += 50;
            right += 50;
      }
      if (abs(left) > 150) left = 150 * (abs(left) / left);
      if (abs(right) > 150) right = 150 * (abs(right) / right);
      robot.motor.Drive(left, right);
      // printf("ProcessTime = %d, LinePosition = %f\n", processTime, robot.line.position);
      // for (uint8_t i = 0; i < 10; i++) printf("%d, ", robot.line.mainVal[i]);
      // printf("\n");
      // 定周期処理
      processTime = processTimer.read_us();
      if (processTime < PERIOD_US) {
            while (processTimer.read_us() < PERIOD_US);
            // #ifdef DEBUG
            // #endif
      } else {
            // printf("OverProcess! ");
      }
}