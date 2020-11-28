/* =====================================================================
   __  __      _____  ______  _   _  _______   _____   ____   _____
   \ \ \ \    / ____||  ____|| \ | ||__   __| / ____| / __ \ |  __ \
 __ \ \ \ \  | (___  | |__   |  \| |   | |   | (___  | |  | || |__) |
 \ \ \ \ \_\  \___ \ |  __|  |     |   | |    \___ \ | |  | ||  _  /
  \ \ \ \     ____) || |____ | |\  |   | |    ____) || |__| || | \ \
   \_\ \_\   |_____/ |______||_| \_|   |_|   |_____/  \____/ |_|  \_\

 Project      : Core Board ESP-07S - Deep Sleep Mode
 Description  : Cycle between wake (on) and deep sleep mode
 Author       : SENTSOR
 Note         : -

===================================================================== */

#define DEBUG_OUT(msg) Serial.print(msg)
#define onboardLed 2

#include <ESP8266WiFi.h>
#include <RTClib.h>

RTC_DS3231 rtc;

void setup() {
  WiFi.mode(WIFI_OFF);
  WiFi.forceSleepBegin();

  rtc.begin();
  rtc.writeSqwPinMode(DS3231_OFF);
  rtc.disable32K();

  pinMode(onboardLed, OUTPUT);
}

void loop() {
  digitalWrite(onboardLed, LOW);
  delay(5000);
  digitalWrite(onboardLed, HIGH);
  ESP.deepSleep(1e+7);
}

// End of File [SENTSOR]
