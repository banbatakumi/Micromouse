#ifndef _CORE0A_MAIN_H_
#define _CORE0A_MAIN_H_

#include "setup.h"

#define CORE0A_CONTROL_FREQ 100  // Hz

void Core0a_setup() {
      Wire.begin();
      Wire.setClock(400000);

      mpu.initialize();

      devStatus = mpu.dmpInitialize();
      mpu.setXAccelOffset(-1572);
      mpu.setYAccelOffset(-2054);
      mpu.setZAccelOffset(678);
      mpu.setXGyroOffset(-46);
      mpu.setYGyroOffset(-28);
      mpu.setZGyroOffset(15);
      if (devStatus == 0) {
            // mpu.CalibrateAccel(5);
            // mpu.CalibrateGyro(5);
            // mpu.PrintActiveOffsets();

            mpu.setDMPEnabled(true);

            packetSize = mpu.dmpGetFIFOPacketSize();
      } else {
            Serial.print(F("DMP Initialization failed (code "));
            Serial.print(devStatus);
            Serial.println(F(")"));
      }
}

void Core0a_loop() {
      if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) {  //  read a packet from FIFO
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
            yaw = SimplifyDeg(ypr[0] * 180 / M_PI - yaw_correction);
      }
      Serial.println(yaw);
}

#endif