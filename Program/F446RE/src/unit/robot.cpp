#include "robot.hpp"

Robot::Robot() {
}

void Robot::hardwareInit() {
      printf("Hello World\n");
      printf("SystemCoreClock = %ld\n", SystemCoreClock);

      fan.init();
      ledH.init();
      lineLed.init();
      motor1a.init();
      motor1b.init();
      motor2a.init();
      motor2b.init();
      buzzer.init();
}