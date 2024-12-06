#ifndef _MAIN_H_
#define _MAIN_H_

#include "setup.h"

#define MAIN_CONTROL_FREQ 10

void main_setup() {
      // WiFiネットワークを作成
      WiFi.softAP(ssid, password);
      IPAddress IP = WiFi.softAPIP();
      Serial.print("AP IP address: ");
      Serial.println(IP);

      server.begin();  // サーバーを起動
}

void main_loop() {
      WiFiClient client = server.available();  // 接続の待機

      if (client) {  // 接続されたとき
            digitalWrite(led1, HIGH);
            while (client.connected()) {  // 接続されている間はデータの受信を続ける
                  // put your main code here, to run repeatedly:if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) {  //  read a packet from FIFO
                  client.println(yaw);
            }
      } else {
            digitalWrite(led1, LOW);
      }
}

#endif