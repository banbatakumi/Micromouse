#include "motorDrive.hpp"

MotorDrive::MotorDrive(PwmSingleOut *motor1a, PwmSingleOut *motor1b, PwmSingleOut *motor2a, PwmSingleOut *motor2b, uint16_t *encoderValLeft, uint16_t *encoderValRight)
    : _motor1a(motor1a), _motor1b(motor1b), _motor2a(motor2a), _motor2b(motor2b) {
      this->_encoderValLeft = encoderValLeft;
      this->_encoderValRight = encoderValRight;
      this->Kp = 2;
      this->Ki = 2;
}

void MotorDrive::init() {
      _motor1a->init();
      _motor1b->init();
      _motor2a->init();
      _motor2b->init();
}
void MotorDrive::encoderCompute() {
      // 最大値を求める
      if (*_encoderValLeft != 0 && *_encoderValRight != 0) {
            if (*_encoderValLeft > encoder.maxValLeft) encoder.maxValLeft = *_encoderValLeft;
            encoder.radLeft = *_encoderValLeft * (2 * PI / encoder.maxValLeft);
            if (*_encoderValRight > encoder.maxValRight) encoder.maxValRight = *_encoderValRight;
            encoder.radRight = *_encoderValRight * (2 * PI / encoder.maxValRight);
            run();
      }
}

int16_t debug[5];

void MotorDrive::run() {
      if ((encoder.preRadLeft != encoder.radLeft || encoder.preRadRight != encoder.radRight) && periodTimer.read_us() > 3000) {
            dt = periodTimer.read_us() / 1000000.0f;
            periodTimer.reset();

            // 角度の差を求める
            encoder.difRadLeft = encoder.radLeft - encoder.preRadLeft;
            encoder.difRadRight = encoder.radRight - encoder.preRadRight;
            encoder.preRadLeft = encoder.radLeft;
            encoder.preRadRight = encoder.radRight;

            // PI以上変わった時に修正
            if (abs(encoder.difRadLeft) > PI) encoder.difRadLeft -= 2 * PI * (abs(encoder.difRadLeft) / encoder.difRadLeft);
            if (abs(encoder.difRadRight) > PI) encoder.difRadRight -= 2 * PI * (abs(encoder.difRadRight) / encoder.difRadRight);

            // rad/sに変換
            encoder.speedLeft = encoder.difRadLeft / dt * -1;
            encoder.speedRight = encoder.difRadRight / dt;

            dLeft = encoder.speedLeft - speedLeft;
            dRight = encoder.speedRight - speedRight;
            iLeft += dLeft * dt;
            iRight += dRight * dt;
            if (abs(iLeft * Ki) > 600) iLeft = 600 / Ki * (abs(iLeft) / iLeft);
            if (abs(iRight * Ki) > 600) iRight = 600 / Ki * (abs(iRight) / iRight);
            if (speedLeft == 0) iLeft *= 0.5;
            if (speedRight == 0) iRight *= 0.5;

            powerLeft = 0 - Kp * dLeft - Ki * iLeft;
            powerRight = 0 - Kp * dRight - Ki * iRight;

            // 範囲保証
            if (abs(powerLeft) > MAX_POWER) powerLeft = MAX_POWER * (abs(powerLeft) / powerLeft);
            if (abs(powerRight) > MAX_POWER) powerRight = MAX_POWER * (abs(powerRight) / powerRight);

            // debug[0] = Kp * dRight;
            // debug[1] = Ki * iRight;
            // debug[2] = powerRight;
            // debug[3] = speedRight;

            init();
            if (powerLeft > 0) {
                  _motor1a->write(powerLeft * 0.001f);
                  _motor1b->write(0);
            } else {
                  _motor1a->write(0);
                  _motor1b->write(powerLeft * -0.001f);
            }
            if (powerRight > 0) {
                  _motor2a->write(powerRight * 0.001f);
                  _motor2b->write(0);
            } else {
                  _motor2a->write(0);
                  _motor2b->write(powerRight * -0.001f);
            }
      }
}

void MotorDrive::drive(int16_t left, int16_t right) {
      speedLeft = left;
      speedRight = right;  // 範囲保証
      if (abs(speedLeft) > MAX_POWER) speedLeft = MAX_POWER * (abs(speedLeft) / speedLeft);
      if (abs(speedRight) > MAX_POWER) speedRight = MAX_POWER * (abs(speedRight) / speedRight);
}

void MotorDrive::brake() {
      _motor1a->write(1);
      _motor1b->write(1);
      _motor2a->write(1);
      _motor2b->write(1);
}