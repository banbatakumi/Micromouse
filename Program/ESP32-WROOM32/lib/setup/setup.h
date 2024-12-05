#ifndef _SETUP_H_
#define _SETUP_H_

#include <WiFi.h>

#include "Adafruit_NeoPixel.h"
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"
#include "simplify_deg.h"

TaskHandle_t thp[3];  // マルチスレッドのタスクハンドル格納用

const char *ssid = "MycroMouseESP32";
const char *password = "12345678";

WiFiServer server(8000);

const int led1 = 25;
const int led2 = 26;
const int led3 = 27;

MPU6050 mpu;

// MPU control/status vars
uint8_t devStatus;       // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;     // expected DMP packet size (default is 42 bytes)
uint8_t fifoBuffer[64];  // FIFO storage buffer

// orientation/motion vars
Quaternion q;         // [w, x, y, z]         quaternion container
VectorFloat gravity;  // [x, y, z]            gravity vector
float ypr[3];         // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

float yaw_correction;  // yaw軸の補正値
int16_t yaw;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(6, 32, NEO_GRB + NEO_KHZ800);

#endif