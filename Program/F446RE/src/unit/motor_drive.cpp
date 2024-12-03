#include "motor_drive.hpp"

MotorDrive::MotorDrive(PwmSingleOut *motor1a, PwmSingleOut *motor1b, PwmSingleOut *motor2a, PwmSingleOut *motor2b, uint16_t *encoder_val_left, uint16_t *encoder_val_right)
    : motor1a_(motor1a), motor1b_(motor1b), motor2a_(motor2a), motor2b_(motor2b) {
      this->encoder_val_left_ = encoder_val_left;
      this->encoder_val_right_ = encoder_val_right;
      this->kp = 3;
      this->ki = 3;

      aveEncoderLeft.SetLength(10);
      aveEncoderRight.SetLength(10);
}

void MotorDrive::Init() {
      motor1a_->init();
      motor1b_->init();
      motor2a_->init();
      motor2b_->init();
}

void MotorDrive::EncoderCompute() {
      if (*encoder_val_left_ != 0 && *encoder_val_right_ != 0) {
            // 最大値を求める
            if (*encoder_val_left_ > encoder.max_val_left) encoder.max_val_left = *encoder_val_left_;
            if (*encoder_val_right_ > encoder.max_val_right) encoder.max_val_right = *encoder_val_right_;
            // radianに変換
            encoder.rad_left = *encoder_val_left_ * (2 * PI / encoder.max_val_left);
            encoder.rad_right = *encoder_val_right_ * (2 * PI / encoder.max_val_right);
            aveEncoderLeft.Compute(&encoder.rad_left);
            aveEncoderRight.Compute(&encoder.rad_right);
            SpeedControl();
      }
}

void MotorDrive::SpeedControl() {
      if (encoder.pre_rad_left != encoder.rad_left || encoder.pre_rad_right != encoder.rad_right) {  // 更新されたら
            dt = periodTimer.read_us() * 0.000001f;                                                  // s
            periodTimer.reset();

            // 角度の差を求める
            encoder.dif_rad_left = encoder.rad_left - encoder.pre_rad_left;
            encoder.dif_rad_right = encoder.rad_right - encoder.pre_rad_right;
            encoder.pre_rad_left = encoder.rad_left;
            encoder.pre_rad_right = encoder.rad_right;

            // PI以上変わった時に修正
            if (abs(encoder.dif_rad_left) > PI) encoder.dif_rad_left -= 2 * PI * (abs(encoder.dif_rad_left) / encoder.dif_rad_left);
            if (abs(encoder.dif_rad_right) > PI) encoder.dif_rad_right -= 2 * PI * (abs(encoder.dif_rad_right) / encoder.dif_rad_right);

            // rad/sに変換
            encoder.speed_left = encoder.dif_rad_left / dt * -1;
            encoder.speed_right = encoder.dif_rad_right / dt;

            // PIの計算
            // 比例成分
            p_left_ = encoder.speed_left - speed_left_;
            p_right_ = encoder.speed_right - speed_right_;
            // 積分成分
            i_left_ += p_left_ * dt;
            i_right_ += p_right_ * dt;
            // 積分値の範囲制限
            if (abs(i_left_ * ki) > 300) i_left_ = 300 / ki * (abs(i_left_) / i_left_);
            if (abs(i_right_ * ki) > 300) i_right_ = 300 / ki * (abs(i_right_) / i_right_);
            // speedが0に指定されたらi成分を減らしていく
            if (speed_left_ == 0) i_left_ *= 0.5;
            if (speed_right_ == 0) i_right_ *= 0.5;
            // 合算
            power_left_ = 0 - kp * p_left_ - ki * i_left_;
            power_right_ = 0 - kp * p_right_ - ki * i_right_;

            // スピードが正の値であればパワーも正の値・これがなかったら動かない
            if (speed_left_ > 0 && power_left_ < 1) power_left_ = 1;
            if (speed_right_ > 0 && power_right_ < 1) power_right_ = 1;
            if (speed_left_ < 0 && power_left_ > -1) power_left_ = -1;
            if (speed_right_ < 0 && power_right_ > -1) power_right_ = -1;

            Run(power_left_, power_right_);
      }
}

void MotorDrive::Run(double left, double right) {
      output_left = left;
      output_right = right;

      // 範囲保証
      if (abs(output_left) > MAX_POWER) output_left = MAX_POWER * (abs(output_left) / output_left);
      if (abs(output_right) > MAX_POWER) output_right = MAX_POWER * (abs(output_right) / output_right);

      // 出力
      Init();  // なぜか毎回PWMをリセットしないと動かない
      if (speed_left_ != 0) {
            if (output_left > 0) {
                  motor1a_->write(output_left * 0.001f);
                  motor1b_->write(0);
            } else {
                  motor1a_->write(0);
                  motor1b_->write(output_left * -0.001f);
            }
      }
      if (speed_right_ != 0) {
            if (output_right > 0) {
                  motor2a_->write(output_right * 0.001f);
                  motor2b_->write(0);
            } else {
                  motor2a_->write(0);
                  motor2b_->write(output_right * -0.001f);
            }
      }
}

void MotorDrive::Drive(int16_t left, int16_t right) {
      speed_left_ = left;
      speed_right_ = right;
      // スピードの範囲保証
      if (abs(speed_left_) > MAX_POWER) speed_left_ = MAX_POWER * (abs(speed_left_) / speed_left_);
      if (abs(speed_right_) > MAX_POWER) speed_right_ = MAX_POWER * (abs(speed_right_) / speed_right_);
}

void MotorDrive::Brake() {
      motor1a_->write(1);
      motor1b_->write(1);
      motor2a_->write(1);
      motor2b_->write(1);
}