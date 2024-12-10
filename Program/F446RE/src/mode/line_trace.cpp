#ifndef __LINE_TRACE__
#define __LINE_TRACE__

#include "mode.hpp"

float p, i, d, pid, pre_p;

void Mode::LineTrace() {
      const float Kp = 1.5, Ki = 2, Kd = 0.03;
      int16_t left, right;
      p = robot->line.position - 0;
      i += p * process_time_ * 0.000001f;
      d = (p - pre_p) / (process_time_ * 0.000001f);
      pre_p = p;
      pid = p * Kp + i * Ki + d * Kd;
      if (abs(p) < 1) i = 0.5;
      left = pid * 2;
      right = pid * -2;
      if (abs(left) > 500) left = 500 * (abs(left) / left);
      if (abs(right) > 500) right = 500 * (abs(right) / right);
      if (abs(robot->line.position) < 5) {
            left += 120;
            right += 120;
      } else {
            left += 60;
            right += 60;
      }
      if (abs(left) > 600) left = 600 * (abs(left) / left);
      if (abs(right) > 600) right = 600 * (abs(right) / right);
      robot->motor.Drive(left, right);
      // printf("left = %d, right = %d\n", left, right);
      // robot->motor.Drive(200, 0);
}

#endif