#ifndef __ROBOT__
#define __ROBOT__

#include "DigitalInOut.hpp"
#include "PWMSingle.hpp"
#include "Timer.hpp"
#include "adc.h"
#include "main.h"

class Robot {
     public:
      Robot();
      void hardwareInit();

      DigitalOut led1 = DigitalOut(LED1_GPIO_Port, LED1_Pin);
      DigitalOut led2 = DigitalOut(LED2_GPIO_Port, LED2_Pin);
      DigitalOut led3 = DigitalOut(LED3_GPIO_Port, LED3_Pin);
      DigitalOut led4 = DigitalOut(LED4_GPIO_Port, LED4_Pin);
      DigitalOut led5 = DigitalOut(LED5_GPIO_Port, LED5_Pin);
      DigitalOut led6 = DigitalOut(LED6_GPIO_Port, LED6_Pin);

      PwmSingleOut fan = PwmSingleOut(&htim3, TIM_CHANNEL_4);

     private:
};

#endif