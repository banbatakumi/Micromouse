#include "motorDrive.hpp"

MotorDrive::MotorDrive(PwmSingleOut *motor1a, PwmSingleOut *motor1b, PwmSingleOut *motor2a, PwmSingleOut *motor2b, uint16_t *encoderLeft, uint16_t *encoderRight)
    : _motor1a(motor1a), _motor1b(motor1b), _motor2a(motor2a), _motor2b(motor2b) {
      this->_encoderLeft = encoderLeft;
      this->_encoderRight = encoderRight;
}

void MotorDrive::init() {
      _motor1a->init();
      _motor1b->init();
      _motor2a->init();
      _motor2b->init();
}

void MotorDrive::encoderCompute() {
      speedLeft = preEncoderLeft - *_encoderLeft;
      preEncoderLeft = *_encoderLeft;
}

void MotorDrive::drive(int8_t left, int8_t right) {
      float left_power = left * 0.01f;
      float right_power = right * 0.01f;
      init();
      if (left_power > 0) {
            _motor1a->write(left_power);
            _motor1b->write(0);
      } else {
            _motor1a->write(0);
            _motor1b->write(left_power * -1);
      }
      if (right_power > 0) {
            _motor2a->write(right_power);
            _motor2b->write(0);
      } else {
            _motor2a->write(0);
            _motor2b->write(right_power * -1);
      }
}

void MotorDrive::brake() {
      _motor1a->write(1);
      _motor1b->write(1);
      _motor2a->write(1);
      _motor2b->write(1);
}