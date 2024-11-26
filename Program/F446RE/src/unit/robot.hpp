#ifndef __ROBOT__
#define __ROBOT__

#include "Button.hpp"
#include "Buzzer.hpp"
#include "DigitalInOut.hpp"
#include "PWMSingle.hpp"
#include "Timer.hpp"
#include "adc.h"
#include "config.h"
#include "main.h"
#include "motor_drive.hpp"

class Robot {
     public:
      Robot();
      struct {
            uint16_t val[LINE_QTY];
            float position;

            uint16_t left_val, right_val;
            uint16_t left_th, right_th;
            bool is_left, is_right;
      } line;
      uint16_t encoder_val_left, encoder_val_right;

      DigitalOut led1 = DigitalOut(LED1_GPIO_Port, LED1_Pin);
      DigitalOut led2 = DigitalOut(LED2_GPIO_Port, LED2_Pin);
      DigitalOut led3 = DigitalOut(LED3_GPIO_Port, LED3_Pin);
      DigitalOut led4 = DigitalOut(LED4_GPIO_Port, LED4_Pin);
      DigitalOut led5 = DigitalOut(LED5_GPIO_Port, LED5_Pin);

      Button button1 = Button(BUTTON1_GPIO_Port, BUTTON1_Pin);
      Button button2 = Button(GPIOB, BUTTON2_Pin);
      Button button3 = Button(GPIOB, BUTTON3_Pin);

      PwmSingleOut fan = PwmSingleOut(&htim3, TIM_CHANNEL_4);
      PwmSingleOut ledH = PwmSingleOut(&htim2, TIM_CHANNEL_2);
      PwmSingleOut lineLed = PwmSingleOut(&htim3, TIM_CHANNEL_3);
      PwmSingleOut motor1a = PwmSingleOut(&htim1, TIM_CHANNEL_1);
      PwmSingleOut motor1b = PwmSingleOut(&htim1, TIM_CHANNEL_2);
      PwmSingleOut motor2a = PwmSingleOut(&htim1, TIM_CHANNEL_3);
      PwmSingleOut motor2b = PwmSingleOut(&htim1, TIM_CHANNEL_4);
      Buzzer buzzer = Buzzer(&htim2, TIM_CHANNEL_3);

      MotorDrive motor = MotorDrive(&motor1a, &motor1b, &motor2a, &motor2b, &encoder_val_left, &encoder_val_right);

      void hardwareInit();
      void getSensors();
      void LineCompute();

      inline __attribute__((always_inline)) void heartBeat() {
            static int i = 0;
            i++;
            ledH.write(abs(MyMath::sinDeg(int(i * (360.0f / 2000.0f)))));
      }

     private:
};

#endif