#include "robot.hpp"

#define DEBUG_PERIOD 10  // ms
#define DEBUG_CNT_NUM (int)((DEBUG_PERIOD * 1000) / PERIOD_US)
class Mode {
     public:
      Mode(Robot* robotPtr) : robot(robotPtr) {}
      void MainMode();
      void LineTrace();

     private:
      Timer processTimer;
      Robot* robot;

      uint16_t process_time_;  // us
      int16_t debug_val_[4][DEBUG_CNT_NUM];
};