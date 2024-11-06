#include "mainMode.hpp"

MainMode::MainMode() {
}

void MainMode::loop() {
      timer.reset();
      robot.getSensors();
      // printf("LinePosition = %d\n", robot.info.line.position);

      while (timer.read_us() < 1000);  // 1ms time control
}