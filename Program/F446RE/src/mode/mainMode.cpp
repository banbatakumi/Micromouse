#include "mainMode.hpp"

MainMode::MainMode() {
}

void MainMode::loop() {
      timer.reset();
      robot.motor.encoderCompute();
      robot.getSensors();
      // printf("LinePosition = %d\n", robot.line.position);
      robot.motor.drive(30, 0);
      printf("%d\n", timer.read_us());
      if (timer.read_us() < 100) HAL_Delay(100 - timer.read_us());  // 1ms time control
}