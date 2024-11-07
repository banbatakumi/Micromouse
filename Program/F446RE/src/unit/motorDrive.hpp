#ifndef __MOTORDRIVE__
#define __MOTORDRIVE__

#include "PWMSingle.hpp"

class MotorDrive {
     public:
      MotorDrive(PwmSingleOut *motor1a, PwmSingleOut *motor1b, PwmSingleOut *motor2a, PwmSingleOut *motor2b, uint16_t *encoderLeft, uint16_t *encoderRight);

      void drive(int8_t left, int8_t right);
      void brake();
      void init();
      void encoderCompute();

     private:
      PwmSingleOut *_motor1a;
      PwmSingleOut *_motor1b;
      PwmSingleOut *_motor2a;
      PwmSingleOut *_motor2b;
      uint16_t *_encoderLeft;
      uint16_t *_encoderRight;

      int16_t speedLeft, speedRight;
      int16_t preEncoderLeft, preEncoderRight;
};

#endif