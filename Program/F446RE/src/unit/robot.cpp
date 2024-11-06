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
      motor1a.init();
      motor1b.init();
      motor2a.init();
      motor2b.init();
      buzzer.init();
}

void Robot::getSensors() {
      int8_t lineVectorX[LINE_QTY] = {-45, -35, -25, -15, -5, 5, 15, 25, 35, 45};
      info.line.mainVal[0] = adcGetVal[4];
      info.line.mainVal[1] = adcGetVal[5];
      info.line.mainVal[2] = adcGetVal[6];
      info.line.mainVal[3] = adcGetVal[7];
      info.line.mainVal[4] = adcGetVal[8];
      info.line.mainVal[5] = adcGetVal[9];
      info.line.mainVal[6] = adcGetVal[10];
      info.line.mainVal[7] = adcGetVal[11];
      info.line.mainVal[8] = adcGetVal[12];
      info.line.mainVal[9] = adcGetVal[13];
      info.line.position = 0;
      for (uint8_t i = 0; i < 10; i++) {
            info.line.position += info.line.mainVal[i] * lineVectorX[i];
      }

      info.line.leftVal = adcGetVal[0];
      info.line.rightVal = adcGetVal[1];
}