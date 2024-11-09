#include "mainMode.hpp"

// #define DEBUG

MainMode::MainMode() {
}

void MainMode::loop() {
      processTimer.reset();
      robot.motor.encoderCompute();
      robot.getSensors();
      robot.motor.drive(150, 150);

      // 定周期処理
      processTime = processTimer.read_us();
      if (processTime < PERIOD_US) {
            while (processTimer.read_us() < PERIOD_US);
      } else {
            printf("OverProcess! ");
      }
}