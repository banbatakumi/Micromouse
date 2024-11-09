#include "motorDrive.hpp"

MotorDrive::MotorDrive(PwmSingleOut *motor1a, PwmSingleOut *motor1b, PwmSingleOut *motor2a, PwmSingleOut *motor2b, uint16_t *encoderValLeft, uint16_t *encoderValRight)
    : _motor1a(motor1a), _motor1b(motor1b), _motor2a(motor2a), _motor2b(motor2b) {
      this->_encoderValLeft = encoderValLeft;
      this->_encoderValRight = encoderValRight;
}

void MotorDrive::init() {
      _motor1a->init();
      _motor1b->init();
      _motor2a->init();
      _motor2b->init();
}

void MotorDrive::encoderCompute() {
      // 最大値を求める
      if (*_encoderValLeft > MaxValLeft) MaxValLeft = *_encoderValLeft;
      RadLeft = *_encoderValLeft * (2 * PI / MaxValLeft);
      if (*_encoderValRight > MaxValRight) MaxValRight = *_encoderValRight;
      RadRight = *_encoderValRight * (2 * PI / MaxValRight);

      // 角度の差を求める
      difRadLeft = preRadLeft - RadLeft;
      difRadRight = preRadRight - RadRight;
      // PI以上変わった時に修正
      if (abs(difRadLeft) > PI) difRadLeft -= 2 * PI * (abs(difRadLeft) / difRadLeft);
      if (abs(difRadRight) > PI) difRadRight -= 2 * PI * (abs(difRadRight) / difRadRight);

      // rad/sに変換
      speedLeft = difRadLeft / (periodTimer.read_us() / 1000000.0f);
      speedRight = difRadRight / (periodTimer.read_us() / 1000000.0f);
      preRadLeft = RadLeft;
      periodTimer.reset();
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