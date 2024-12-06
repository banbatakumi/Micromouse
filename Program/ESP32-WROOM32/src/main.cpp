#include "main.h"

#include <Arduino.h>

#include "core0a_main.h"
#include "core1a_main.h"
#include "core1b_main.h"

void Core0a(void *args) {
      const uint32_t control_period = (1.0f) / CORE0A_CONTROL_FREQ * 1000000;  // Hz→μsに変換
      Core0a_setup();

      while (1) {
            uint64_t current_time = micros();  // 現在経過時間を取得

            Core0a_loop();

            delay(1);
            int32_t extra_time = control_period - (micros() - current_time);  // 処理にかかった時間と余剰時間の差
            if (extra_time > 0) {
                  delayMicroseconds(extra_time);
            } else {
                  // Serial.println("Core0a processing time exceeded");
            }
      }
}

void Core1a(void *args) {
      const uint32_t control_period = (1.0f) / CORE1A_CONTROL_FREQ * 1000000;  // Hz→μsに変換
      Core1a_setup();
      while (1) {
            uint64_t current_time = micros();  // 現在経過時間を取得
            Core1a_loop();

            delay(1);
            int32_t extra_time = control_period - (micros() - current_time);  // 処理にかかった時間と余剰時間の差
            if (extra_time > 0) {
                  delayMicroseconds(extra_time);
            } else {
                  // Serial.println("Core0b processing time exceeded");
            }
      }
}
void Core1b(void *args) {
      const uint32_t control_period = (1.0f) / CORE1B_CONTROL_FREQ * 1000000;  // Hz→μsに変換
      Core1b_setup();

      while (1) {
            uint64_t current_time = micros();  // 現在経過時間を取得
            Core1b_loop();

            delay(1);
            int32_t extra_time = control_period - (micros() - current_time);  // 処理にかかった時間と余剰時間の差
            if (extra_time > 0) {
                  delayMicroseconds(extra_time);
            } else {
                  // Serial.println("Core0b processing time exceeded");
            }
      }
}

void setup() {
      Serial.begin(115200);
      Serial.println("device start");

      strip.begin();
      for (uint8_t i = 0; i < 6; i++) {
            for (uint8_t j = 0; j < 20; j++) {
                  strip.setPixelColor(i, strip.Color(j, 0, j));
                  strip.show();
                  delay(1);
            }
      }

      pinMode(led1, OUTPUT);
      pinMode(led2, OUTPUT);
      pinMode(led3, OUTPUT);

      main_setup();

      xTaskCreatePinnedToCore(Core0a, "Core0a", 4096, NULL, 1, &thp[0], 0);
      // xTaskCreatePinnedToCore(Core1a, "Core1a", 4096, NULL, 2, &thp[1], 1);
      // xTaskCreatePinnedToCore(Core1b, "Core1b", 4096, NULL, 3, &thp[2], 1);
}

void loop() {
      const uint32_t control_period = (1.0f) / MAIN_CONTROL_FREQ * 1000000;  // Hz→μsに変換
      while (1) {
            uint64_t current_time = micros();  // 現在経過時間を取得

            main_loop();

            int32_t extra_time = control_period - (micros() - current_time);  // 処理にかかった時間と余剰時間の差
            if (extra_time > 0) {
                  delayMicroseconds(extra_time);
            } else {
                  // Serial.println("Core0b processing time exceeded");
            }
      }
}