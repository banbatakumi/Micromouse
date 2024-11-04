#include "app.h"

#include "robot.hpp"

Robot robot;

void setup() {
      printf("Hello World");
      robot.hardwareInit();
}

void main_app() {
      HAL_Delay(250);  // Delay 500ms
}