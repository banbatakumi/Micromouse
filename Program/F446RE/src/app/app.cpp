#include "app.h"

#include "adc.h"
#include "robot.hpp"

Robot robot;
void TimInterrupt1khz() {
      robot.heartBeat();
}
uint16_t result[14];

void setup() {
      robot.hardwareInit();
      HAL_ADC_Start(&hadc1);
      robot.lineLed.write(1);

      robot.buzzer.sound(500, 50);
      HAL_Delay(50);
      robot.buzzer.sound(1500, 50);
      HAL_Delay(50);
      HAL_ADC_Start_DMA(&hadc1, (uint32_t *)&result, 14);
}

void main_app() {
      // uint16_t val[14];

      for (uint8_t i = 0; i < 14; i++) {
            // HAL_ADC_PollForConversion(&hadc1, 100);
            // val[i] = HAL_ADC_GetValue(&hadc1);
            printf(", %d =   %ld", i, result[i]);
      }
      printf("\n");
      HAL_Delay(100);
}