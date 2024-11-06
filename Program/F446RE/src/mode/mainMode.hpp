#include "robot.hpp"

class MainMode {
     public:
      MainMode();
      void loop();

     private:
      Timer timer;
      // Robot *robot;
      Robot robot;
};