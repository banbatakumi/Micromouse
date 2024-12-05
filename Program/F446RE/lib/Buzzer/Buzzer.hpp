#ifndef __BUZZER__
#define __BUZZER__

#include "tim.h"

#ifdef __cplusplus
extern "C" {

class Buzzer {
     public:
      Buzzer(TIM_HandleTypeDef *htim, uint32_t channel)
          : _htim(htim), _channel(channel), _maxValue(_htim->Init.Period) {
      }

      void init() {
            HAL_TIM_PWM_Start(_htim, _channel);
            _maxValue = _htim->Init.Period;
      }

      void sound(uint16_t period, uint16_t time) {
            // 周波数変更
            _htim->Init.Prescaler = 9;
            _htim->Init.Period = (SystemCoreClock / (period * (_htim->Init.Prescaler + 1))) - 1;
            if (HAL_TIM_Base_Init(_htim) != HAL_OK) {
                  Error_Handler();
            }

            float duty = (int)(0.5 * _maxValue);  // duty比を0.5にする

            // 出力
            __HAL_TIM_SET_COMPARE(_htim, _channel, duty);
            HAL_Delay(time);
            __HAL_TIM_SET_COMPARE(_htim, _channel, 0);
      }

     private:
      TIM_HandleTypeDef *_htim;
      uint32_t _channel;
      uint32_t _maxValue;

      bool _usePwmPin_t;
};
};

#endif
#endif