#ifndef __MOTORDRIVE__
#define __MOTORDRIVE__

#include "PWMSingle.hpp"
#include "Timer.hpp"

class MotorDrive {
     public:
      MotorDrive(PwmSingleOut *motor1a, PwmSingleOut *motor1b, PwmSingleOut *motor2a, PwmSingleOut *motor2b, uint16_t *encoderValLeft, uint16_t *encoderValRight);

      void drive(int8_t left, int8_t right);
      void brake();
      void init();
      void encoderCompute();
      float speedLeft, speedRight;

     private:
      PwmSingleOut *_motor1a;
      PwmSingleOut *_motor1b;
      PwmSingleOut *_motor2a;
      PwmSingleOut *_motor2b;
      uint16_t *_encoderValLeft;
      uint16_t *_encoderValRight;

      Timer periodTimer;

      float preRadLeft, preRadRight;
      float RadLeft, RadRight;
      float difRadLeft, difRadRight;
      uint16_t MaxValLeft, MaxValRight;
};

#endif