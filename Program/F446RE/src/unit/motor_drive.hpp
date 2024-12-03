#ifndef __MOTORDRIVE__
#define __MOTORDRIVE__

#include "MovingAve.hpp"
#include "PWMSingle.hpp"
#include "Timer.hpp"

#define MAX_POWER 600
#define MIN_POWER 20

class MotorDrive {
     public:
      MotorDrive(PwmSingleOut *motor1a, PwmSingleOut *motor1b, PwmSingleOut *motor2a, PwmSingleOut *motor2b, uint16_t *encoder_val_left, uint16_t *encoder_val_right);

      void Drive(int16_t left, int16_t right);
      void Run(double left, double right);
      void SpeedControl();
      void Brake();
      void Init();
      void EncoderCompute();

      struct {
            double speed_left, speed_right;
            double pre_rad_left, pre_rad_right;
            double rad_left, rad_right;
            double dif_rad_left, dif_rad_right;
            uint16_t max_val_left, max_val_right;
      } encoder;

     private:
      PwmSingleOut *motor1a_;
      PwmSingleOut *motor1b_;
      PwmSingleOut *motor2a_;
      PwmSingleOut *motor2b_;
      uint16_t *encoder_val_left_;
      uint16_t *encoder_val_right_;

      MovingAve aveEncoderLeft;
      MovingAve aveEncoderRight;

      Timer periodTimer;

      int16_t speed_left_, speed_right_;
      double power_left_, power_right_;
      double p_left_, p_right_;
      double i_left_, i_right_;

      double dt;
      double kp, ki;

      double output_left;
      double output_right;
};

#endif