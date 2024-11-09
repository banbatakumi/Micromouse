#ifndef __MOTORDRIVE__
#define __MOTORDRIVE__

#include "PWMSingle.hpp"
#include "Timer.hpp"

#define MAX_POWER 600
#define MIN_POWER 140
class MotorDrive {
     public:
      MotorDrive(PwmSingleOut *motor1a, PwmSingleOut *motor1b, PwmSingleOut *motor2a, PwmSingleOut *motor2b, uint16_t *encoderValLeft, uint16_t *encoderValRight);

      void drive(int16_t left, int16_t right);
      void run();
      void brake();
      void init();
      void encoderCompute();

     private:
      PwmSingleOut *_motor1a;
      PwmSingleOut *_motor1b;
      PwmSingleOut *_motor2a;
      PwmSingleOut *_motor2b;
      uint16_t *_encoderValLeft;
      uint16_t *_encoderValRight;

      Timer periodTimer;
      struct {
            double speedLeft, speedRight;
            double preRadLeft, preRadRight;
            double radLeft, radRight;
            double difRadLeft, difRadRight;
            uint16_t maxValLeft, maxValRight;
      } encoder;

      int16_t powerLeft, powerRight;
      int16_t speedLeft, speedRight;

      double dLeft, dRight;
      double iLeft, iRight;

      double dt;
      double Kp, Ki;
};

#endif