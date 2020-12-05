/* =====================================================================
   __  __      _____  ______  _   _  _______   _____   ____   _____
   \ \ \ \    / ____||  ____|| \ | ||__   __| / ____| / __ \ |  __ \
 __ \ \ \ \  | (___  | |__   |  \| |   | |   | (___  | |  | || |__) |
 \ \ \ \ \_\  \___ \ |  __|  |     |   | |    \___ \ | |  | ||  _  /
  \ \ \ \     ____) || |____ | |\  |   | |    ____) || |__| || | \ \
   \_\ \_\   |_____/ |______||_| \_|   |_|   |_____/  \____/ |_|  \_\

 Project      : Core Board ESP-07S - WiFi Handler
 Description  : Handle WiFi connectivity: connecting to assigned AP,
                connection check, automatic reconnect
 Author       : SENTSOR
 Note         : -

===================================================================== */

#define DEBUG_OUT(msg) Serial.print(msg)
#define onboardLed 2
//WiFi credentials
#define WIFI_SSID "WIFI_SSID"
#define WIFI_PASSWORD "WIFI_PASSWORD"
//Connection parameter
#define CONNECTION_TIMEOUT 5000UL
#define RETRY_ATTEMP 3

#include <ESP8266WiFi.h>

void setup() {
  Serial.begin(115200, SERIAL_8N1);
  delay(500);
  DEBUG_OUT(F("\n"));

  pinMode(onboardLed, OUTPUT);

  initWiFi();
}

void loop() {
  if (connectionCheck()) {
    //Do something that need WiFi connection
    static uint32_t lastMillis;
    if (millis() - lastMillis >= 500L) {
      lastMillis = millis();
      heartbeat(1);
    }
  }
  else {
    //Reconnect
    initWiFi();
  }
}

boolean initWiFi() {
  DEBUG_OUT(F("DEBUG >> WiFi initialization, restarting modem...\n"));

  DEBUG_OUT(F("DEBUG >> Turning off WiFi... "));
  WiFi.mode(WIFI_OFF);
  WiFi.forceSleepBegin();
  delay(1000);
  DEBUG_OUT(F("OK\n"));

  DEBUG_OUT(F("DEBUG >> Turning on WiFi... "));
  WiFi.forceSleepWake();
  WiFi.mode(WIFI_STA);
  delay(1000);
  DEBUG_OUT(F("OK\n"));

  uint32_t startTimer;
  for (uint8_t attemp = 0; attemp < RETRY_ATTEMP; attemp++) {
    DEBUG_OUT("DEBUG >> ATT:" + String(attemp + 1) + " Connecting to AP... ");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    startTimer = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startTimer < CONNECTION_TIMEOUT) {
      delay(100);
    }
    if (WiFi.status() == WL_CONNECTED) {
      DEBUG_OUT(F("Connected\n"));
      DEBUG_OUT("DEBUG >> IPv4=" + WiFi.localIP().toString() + "\n");
      delay(100);
      return true;
    }
    else {
      DEBUG_OUT(F("Timeout\n"));
      WiFi.disconnect();
      delay(100);
    }
  }

  DEBUG_OUT(F("DEBUG >> WiFi not connected\n"));
  DEBUG_OUT(F("DEBUG >> Retry attempts exceeded\n"));
  return false;
}

boolean connectionCheck() {
  if (WiFi.status() == WL_CONNECTED) return true;
  else return false;
}

void heartbeat(uint8_t n) {
  //Blink indicator LED for n-times
  while (n > 0) {
    digitalWrite(onboardLed, LOW);
    delay(10);
    digitalWrite(onboardLed, HIGH);
    delay(100);
    n--;
  }
}

// End of File [SENTSOR]
