#include "robot.hpp"

Robot::Robot() {
}

void Robot::hardwareInit() {
      printf("Hello World\n");
      fan.init();
      led1 = 1;
      led2 = 1;
      led3 = 1;
}