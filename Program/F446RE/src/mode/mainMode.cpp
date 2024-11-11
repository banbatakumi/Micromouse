#include "mainMode.hpp"

// #define DEBUG

MainMode::MainMode() {
}

void MainMode::loop() {
      processTimer.reset();
      robot.motor.encoderCompute();
      // robot.getSensors();
      // int16_t left, right;
      // left = robot.line.position / 50;
      // right = robot.line.position / -50;
      // if (abs(left) > 75) left = 75 * (abs(left) / left);
      // if (abs(right) > 75) right = 75 * (abs(right) / right);
      // if (abs(robot.line.position) < 1000) {
      //       left += 90;
      //       right += 90;
      // } else {
      //       left += 30;
      //       right += 30;
      // }
      // if (abs(left) > 150) left = 150 * (abs(left) / left);
      // if (abs(right) > 150) right = 150 * (abs(right) / right);
      // robot.motor.drive(200, 0);

      // 定周期処理
      processTime = processTimer.read_us();
      if (processTime < PERIOD_US) {
            while (processTimer.read_us() < PERIOD_US);
#ifdef DEBUG
            printf("%d\n", robot.line.position);
#endif
      } else {
            printf("OverProcess! ");
      }
}