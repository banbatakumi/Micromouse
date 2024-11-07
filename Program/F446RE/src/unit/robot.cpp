#include "robot.hpp"

uint16_t adcGetVal[14];

Robot::Robot() {
}

void Robot::hardwareInit() {
      printf("Hello World\n");
      printf("SystemCoreClock = %ld\n", SystemCoreClock);

      HAL_ADC_Start(&hadc1);
      HAL_ADC_Start_DMA(&hadc1, (uint32_t *)&adcGetVal, 14);

      fan.init();
      ledH.init();
      lineLed.init();
      // motor1a.init();
      // motor1b.init();
      // motor2a.init();
      // motor2b.init();
      buzzer.init();
}

void Robot::getSensors() {
      float lineVectorX[LINE_QTY] = {-4.5, -3.5, -2.5, -1.5, -0.5, 0.5, 1.5, 2.5, 3.5, 4.5};
      line.mainVal[0] = adcGetVal[4];
      line.mainVal[1] = adcGetVal[5];
      line.mainVal[2] = adcGetVal[6];
      line.mainVal[3] = adcGetVal[7];
      line.mainVal[4] = adcGetVal[8];
      line.mainVal[5] = adcGetVal[9];
      line.mainVal[6] = adcGetVal[10];
      line.mainVal[7] = adcGetVal[11];
      line.mainVal[8] = adcGetVal[12];
      line.mainVal[9] = adcGetVal[13];
      line.position = 0;
      for (uint8_t i = 0; i < 10; i++) {
            line.position += line.mainVal[i] * lineVectorX[i];
      }
      line.position *= -1;

      encoderLeft = adcGetVal[0];
      encoderRight = adcGetVal[1];
}