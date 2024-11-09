#include "robot.hpp"

#define DEBUG_PERIOD 10  // ms
#define DEBUG_CNT_NUM (int)((DEBUG_PERIOD * 1000) / PERIOD_US)
class MainMode {
     public:
      MainMode();
      void loop();

     private:
      Timer processTimer;
      // Robot *robot;
      Robot robot;

      uint16_t processTime;  // us
      uint16_t debugCnt;
      int16_t debugVal[4][DEBUG_CNT_NUM];
};