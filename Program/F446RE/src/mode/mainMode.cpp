#include "mainMode.hpp"

#define DEBUG
#define DEBUG_PERIOD 100  // ms

MainMode::MainMode() {
}

void MainMode::loop() {
      processTimer.reset();
      robot.motor.encoderCompute();
      robot.getSensors();
      robot.motor.drive(15, 0);

      // 定周期処理
      uint16_t period_us = (1.0f / MAIN_FREQ) * 1000000;
      ProcessTime = processTimer.read_us();
      if (ProcessTime < period_us) {
#ifdef DEBUG
            debugCnt++;
            if (debugCnt >= ((DEBUG_PERIOD * 1000) / period_us)) {
                  debugCnt = 0;
            }
            printf("ProcessTime = %ldus, LinePosition = %f\n", ProcessTime, robot.motor.speedLeft);
            while (processTimer.read_us() < period_us);
#endif
      } else {
            printf("OverProcess! ");
      }
}