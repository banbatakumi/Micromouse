#include "robot.hpp"

class MainMode {
     public:
      MainMode();
      void loop();

     private:
      Timer processTimer;
      // Robot *robot;
      Robot robot;

      uint32_t ProcessTime;  // us
      uint32_t debugCnt;
};