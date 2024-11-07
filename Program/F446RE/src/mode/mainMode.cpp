#include "mainMode.hpp"

MainMode::MainMode() {
}

void MainMode::loop() {
      timer.reset();
      robot.getSensors();
      printf("LinePosition = %d\n", robot.line.position);
      int16_t left, right;
      left = robot.line.position / 10;
      right = robot.line.position / -10;
      if (abs(robot.line.position) < 200) {
            left += 10;
            right += 10;
      }
      if (abs(left) > 20) left = 20 * (abs(left) / left);
      if (abs(right) > 20) right = 20 * (abs(right) / right);
      robot.motor.drive(left, right);
      while (timer.read_us() < 1000);  // 1ms time control
}