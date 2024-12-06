#ifndef __LINE_TRACE__
#define __LINE_TRACE__

#include "mode.hpp"

float p, i, d, pid, pre_p;

void Mode::LineTrace() {
      const float Kp = 2.5, Ki = 1, Kd = 0.02;
      int16_t left, right;
      p = robot->line.position - 0;
      // i += p * processTime * 0.000001f;
      // d = (p - pre_p) / (processTime * 0.000001f);
      pre_p = p;
      pid = p * Kp + i * Ki + d * Kd;
      if (abs(p) < 1) i = 0.5;
      left = pid * 2;
      right = pid * -2;
      if (abs(left) > 200) left = 200 * (abs(left) / left);
      if (abs(right) > 200) right = 200 * (abs(right) / right);
      if (abs(robot->line.position) < 5) {
            left += 30;
            right += 30;
      } else {
            left += 20;
            right += 20;
      }
      if (abs(left) > 200) left = 200 * (abs(left) / left);
      if (abs(right) > 200) right = 200 * (abs(right) / right);
      // robot->motor.Drive(left, right);
      // printf("left = %d, right = %d\n", left, right);
}

#endif