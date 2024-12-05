#include <Arduino.h>
#include <WiFi.h>

#include "Adafruit_NeoPixel.h"
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"
#include "simplify_deg.h"

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

void setup() {
      Serial.begin(115200);
      Serial.println("device start");
      Wire.begin();
      Wire.setClock(400000);
      strip.begin();
      for (uint8_t i = 0; i < 6; i++) {
            for (uint8_t j = 0; j < 20; j++) {
                  strip.setPixelColor(i, strip.Color(0, 0, j));
                  strip.show();
                  delay(1);
            }
      }

      mpu.initialize();

      devStatus = mpu.dmpInitialize();
      mpu.setXAccelOffset(-3428);
      mpu.setYAccelOffset(-308);
      mpu.setZAccelOffset(882);
      mpu.setXGyroOffset(-328);
      mpu.setYGyroOffset(-534);
      mpu.setZGyroOffset(-106);
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
      pinMode(led1, OUTPUT);
      pinMode(led2, OUTPUT);
      pinMode(led3, OUTPUT);

      // WiFiネットワークを作成
      WiFi.softAP(ssid, password);
      IPAddress IP = WiFi.softAPIP();
      Serial.print("AP IP address: ");
      Serial.println(IP);

      server.begin();  // サーバーを起動
}

void loop() {
      // Serial.println(yaw);
      WiFiClient client = server.available();  // 接続の待機

      if (client) {  // 接続されたとき
            Serial.println("New Client.");

            while (client.connected()) {  // 接続されている間はデータの受信を続ける
                  // put your main code here, to run repeatedly:if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) {  //  read a packet from FIFO

                  digitalWrite(led1, HIGH);
                  digitalWrite(led2, HIGH);
                  digitalWrite(led3, HIGH);

                  if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) {  //  read a packet from FIFO
                        mpu.dmpGetQuaternion(&q, fifoBuffer);
                        mpu.dmpGetGravity(&gravity, &q);
                        mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
                        yaw = SimplifyDeg(ypr[0] * 180 / M_PI - yaw_correction);
                  }
                  int cnt = yaw;

                  client.println(cnt);
                  delay(1);
            }
      }
}
