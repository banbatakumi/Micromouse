#include "motorDrive.hpp"

MotorDrive::MotorDrive(PwmSingleOut *motor1a, PwmSingleOut *motor1b, PwmSingleOut *motor2a, PwmSingleOut *motor2b, uint16_t *encoderValLeft, uint16_t *encoderValRight)
    : _motor1a(motor1a), _motor1b(motor1b), _motor2a(motor2a), _motor2b(motor2b) {
      this->_encoderValLeft = encoderValLeft;
      this->_encoderValRight = encoderValRight;
      this->Kp = 6;
      this->Ki = 3;
}

void MotorDrive::init() {
      _motor1a->init();
      _motor1b->init();
      _motor2a->init();
      _motor2b->init();
}
void MotorDrive::encoderCompute() {
      if (*_encoderValLeft != 0 && *_encoderValRight != 0) {  // 初期状態で値が代入されておらずnanになるのを防ぐ
            // 最大値を求める
            if (*_encoderValLeft > encoder.maxValLeft) encoder.maxValLeft = *_encoderValLeft;
            encoder.radLeft = *_encoderValLeft * (2 * PI / encoder.maxValLeft);
            if (*_encoderValRight > encoder.maxValRight) encoder.maxValRight = *_encoderValRight;
            encoder.radRight = *_encoderValRight * (2 * PI / encoder.maxValRight);
            run();
      }
}

void MotorDrive::run() {
      printf("%f, %f\n", encoder.radLeft, encoder.radRight);
      if (encoder.preRadLeft != encoder.radLeft || encoder.preRadRight != encoder.radRight) {  // 更新されたら
            dt = periodTimer.read_us() / 1000000.0f;                                           // s
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

            // PIの計算
            // 比例成分
            dLeft = encoder.speedLeft - speedLeft;
            dRight = encoder.speedRight - speedRight;
            // 積分成分
            iLeft += dLeft * dt;
            iRight += dRight * dt;
            // 積分値の範囲制限
            if (abs(iLeft * Ki) > 300) iLeft = 300 / Ki * (abs(iLeft) / iLeft);
            if (abs(iRight * Ki) > 300) iRight = 300 / Ki * (abs(iRight) / iRight);
            // speedが0に指定されたらi成分を減らしていく
            if (speedLeft == 0) iLeft *= 0.5;
            if (speedRight == 0) iRight *= 0.5;
            // 合算
            powerLeft = 0 - Kp * dLeft - Ki * iLeft;
            powerRight = 0 - Kp * dRight - Ki * iRight;

            // スピードが正の値であればパワーも正の値・これがなかったら動かない
            if (speedLeft > 0 && powerLeft < 1) powerLeft = 1;
            if (speedRight > 0 && powerRight < 1) powerRight = 1;
            if (speedLeft < 0 && powerLeft > -1) powerLeft = -1;
            if (speedRight < 0 && powerRight > -1) powerRight = -1;

            // 範囲保証
            if (abs(powerLeft) > MAX_POWER) powerLeft = MAX_POWER * (abs(powerLeft) / powerLeft);
            if (abs(powerRight) > MAX_POWER) powerRight = MAX_POWER * (abs(powerRight) / powerRight);

            // 出力
            init();  // なぜか毎回PWMをリセットしないと動かない
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
      speedRight = right;
      // 範囲保証
      if (abs(speedLeft) > MAX_POWER) speedLeft = MAX_POWER * (abs(speedLeft) / speedLeft);
      if (abs(speedRight) > MAX_POWER) speedRight = MAX_POWER * (abs(speedRight) / speedRight);
}

void MotorDrive::brake() {
      _motor1a->write(1);
      _motor1b->write(1);
      _motor2a->write(1);
      _motor2b->write(1);
}