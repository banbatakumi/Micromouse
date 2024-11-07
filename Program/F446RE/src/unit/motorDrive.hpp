#ifndef __MOTORDRIVE__
#define __MOTORDRIVE__

#include "PWMSingle.hpp"

class MotorDrive {
     public:
      MotorDrive(PwmSingleOut *motor1a, PwmSingleOut *motor1b, PwmSingleOut *motor2a, PwmSingleOut *motor2b);

      void drive(int8_t left, int8_t right);
      void brake();
      void init();

     private:
      PwmSingleOut *_motor1a;
      PwmSingleOut *_motor1b;
      PwmSingleOut *_motor2a;
      PwmSingleOut *_motor2b;
};

#endif