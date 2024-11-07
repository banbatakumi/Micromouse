#include "app.h"

#include "mainMode.hpp"
#include "robot.hpp"

Robot robot;
MainMode mainMode;

void TimInterrupt1khz() {
      robot.heartBeat();
}

void TimInterrupt10khz() {
}

void setup() {
      robot.hardwareInit();
      robot.lineLed.write(1);

      robot.buzzer.sound(500, 50);
      HAL_Delay(50);
      robot.buzzer.sound(1500, 50);
      HAL_Delay(50);

      for (float i = 0; i < 0.05; i += 0.001) {
            robot.fan.write(i);
            HAL_Delay(100);
      }
}

void main_app() {
      while (1) {
            mainMode.loop();
      }
}