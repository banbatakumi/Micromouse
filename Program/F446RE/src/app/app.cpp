#include "app.h"

#include "main_mode.hpp"
#include "robot.hpp"

Robot robot;
MainMode mainMode;

void TimInterrupt1khz() {
      robot.heartBeat();
}

void setup() {
      robot.hardwareInit();
      robot.lineLed.write(0.5);

      robot.buzzer.sound(500, 50);
      HAL_Delay(50);
      robot.buzzer.sound(1500, 50);
      HAL_Delay(50);

      for (float i = 0; i < 0.1; i += 0.001) {
            robot.fan.write(i);
            HAL_Delay(10);
      }
}

void main_app() {
      while (1) {
            mainMode.loop();
      }
}