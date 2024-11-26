#include "robot.hpp"

uint16_t adc_get_val[14];

Robot::Robot() {
}

void Robot::hardwareInit() {
      printf("Hello World\n");
      printf("SystemCoreClock = %ld\n", SystemCoreClock);

      HAL_ADC_Start(&hadc1);
      HAL_ADC_Start_DMA(&hadc1, (uint32_t *)&adc_get_val, 14);
      for (uint8_t i = 0; i < LINE_QTY; i++) {
            // while (!(adc_get_val[i] > 0));
      }
      printf("ADC_DMA start\n");

      // 諸々の初期化
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
      line.val[0] = adc_get_val[13];
      line.val[1] = adc_get_val[12];
      line.val[2] = adc_get_val[11];
      line.val[3] = adc_get_val[10];
      line.val[4] = adc_get_val[9];
      line.val[5] = adc_get_val[8];
      line.val[6] = adc_get_val[7];
      line.val[7] = adc_get_val[6];
      line.val[8] = adc_get_val[5];
      line.val[9] = adc_get_val[4];

      encoder_val_left = adc_get_val[0];
      encoder_val_right = adc_get_val[1];
      line.left_val = adc_get_val[3];
      line.right_val = adc_get_val[2];
      LineCompute();
}

void Robot::LineCompute() {
      float lineVectorX[LINE_QTY] = {-45, -35, -25, -15, -5, 5, 15, 25, 35, 45};
#ifdef WHITE_LINE
      uint16_t min_val = 65535;
      uint8_t min_val_num;
      for (uint8_t i = 0; i < 10; i++) {
            if (min_val > line.val[i]) {
                  min_val = line.val[i];
                  min_val_num = i;
            }
      }
      uint32_t sum = 0;
      float val[10];
      for (uint8_t i = 0; i < LINE_QTY; i++) {
            val[i] = line.val[i];
            if (abs(min_val_num - i) > 2) val[i] = 0;
      }
      uint16_t max_val = 0;
      for (uint8_t i = 0; i < LINE_QTY; i++) {
            if (max_val < val[i] && val[i] != 0) {
                  max_val = val[i];
            }
      }
      for (int8_t i = 0; i < LINE_QTY; i++) {
            if (val[i] != 0) val[i] = max_val - val[i];
            sum += val[i];
      }
      for (uint8_t i = 0; i < LINE_QTY; i++) {
            val[i] *= (1.0f / sum);
      }
      line.position = 0;
      for (uint8_t i = 0; i < LINE_QTY; i++) {
            line.position += val[i] * lineVectorX[i];
      }
#endif
#ifdef BLACK_LINE
      uint16_t max_val = 0;
      uint8_t max_val_num;
      for (uint8_t i = 0; i < 10; i++) {
            if (max_val < line.val[i]) {
                  max_val = line.val[i];
                  max_val_num = i;
            }
      }
      uint32_t sum = 0;
      float val[10];
      for (uint8_t i = 0; i < LINE_QTY; i++) {
            val[i] = line.val[i];
            if (abs(max_val_num - i) > 2) val[i] = 0;
      }
      uint16_t min_val = 65535;
      for (uint8_t i = 0; i < LINE_QTY; i++) {
            if (min_val > val[i] && val[i] != 0) {
                  min_val = val[i];
            }
      }
      for (int8_t i = 0; i < LINE_QTY; i++) {
            if (val[i] != 0) val[i] -= min_val;
            sum += val[i];
      }
      for (uint8_t i = 0; i < LINE_QTY; i++) {
            val[i] *= (1.0f / sum);
      }
      line.position = 0;
      for (uint8_t i = 0; i < LINE_QTY; i++) {
            line.position += val[i] * lineVectorX[i];
      }
#endif
}