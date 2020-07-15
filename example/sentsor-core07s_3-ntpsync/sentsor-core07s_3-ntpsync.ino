/* =====================================================================
   __  __      _____  ______  _   _  _______   _____   ____   _____ 
   \ \ \ \    / ____||  ____|| \ | ||__   __| / ____| / __ \ |  __ \    
 __ \ \ \ \  | (___  | |__   |  \| |   | |   | (___  | |  | || |__) |   
 \ \ \ \ \_\  \___ \ |  __|  |     |   | |    \___ \ | |  | ||  _  /    
  \ \ \ \     ____) || |____ | |\  |   | |    ____) || |__| || | \ \    
   \_\ \_\   |_____/ |______||_| \_|   |_|   |_____/  \____/ |_|  \_\   

 Project      : Core Board ESP-07S - NTP Sync
 Description  : Sync on-board RTC with NTP once
 Author       : SENTSOR
 Version      : 1.0.0 - Initial Build
 Note         : NTP-RTC sync also can be scheduled per given interval
 
===================================================================== */

#define DEBUG_OUT(msg) Serial.print(msg)
#define onboardLed 2
//WiFi credentials
#define WIFI_SSID "//SENTSOR//"
#define WIFI_PASSWORD "140310140052"
//Connection parameter
#define CONNECTION_TIMEOUT 5000UL
#define RETRY_ATTEMP 3
#define NTP_SERVER "time.google.com"
//Timezone offset in milliseconds, Indonesia is UTC+7
#define TZ_OFFSET 25200UL

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <RTClib.h>

WiFiUDP ntpUDP;
NTPClient ntp(ntpUDP,NTP_SERVER,TZ_OFFSET);
RTC_DS3231 rtc;
boolean RTCsync=false;

void setup() {
  Serial.begin(9600,SERIAL_8N1);
  delay(500);
  DEBUG_OUT(F("\n"));
  
  pinMode(onboardLed,OUTPUT);

  if(!rtc.begin()) {
    DEBUG_OUT(F("DEBUG >> RTC not initialized\n"));
    DEBUG_OUT(F("DEBUG >> Halt program\n"));
    while(1) {
      //Do nothing if RTC failed to initialized
      heartbeat(3);
      delay(500);
    }
  }

  initWiFi();
}

void loop() {
  if(connectionCheck()) {
    NTPsync();
    
    static uint32_t lastMillis;
    if(millis()-lastMillis>=1000L) {
      lastMillis=millis();
      datetimeStream();
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
  for(uint8_t attemp=0;attemp<RETRY_ATTEMP;attemp++) {
    DEBUG_OUT("DEBUG >> ATT:"+String(attemp+1)+" Connecting to AP... ");
    WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
    startTimer=millis();
    while(WiFi.status()!=WL_CONNECTED && millis()-startTimer<CONNECTION_TIMEOUT) {
      delay(100);
    }
    if(WiFi.status()==WL_CONNECTED) {
      DEBUG_OUT(F("Connected\n"));
      DEBUG_OUT("DEBUG >> IPv4="+WiFi.localIP().toString()+"\n");
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
  if(WiFi.status()==WL_CONNECTED) return true;
  else return false;
}

boolean NTPsync() {
  if(RTCsync) return true;

  uint32_t startTimer;
  for(uint8_t attemp=0;attemp<RETRY_ATTEMP;attemp++) {
    DEBUG_OUT("DEBUG >> ATT:"+String(attemp+1)+" Connecting to NTP server... ");
    ntp.begin();
    startTimer=millis();
    while(!RTCsync && millis()-startTimer<CONNECTION_TIMEOUT) {
      if(ntp.update()) RTCsync=true;
      delay(100);
    }
    if(RTCsync) {
      DEBUG_OUT(F("Connected\n"));
      rtc.adjust(DateTime(ntp.getEpochTime()));
      DEBUG_OUT(F("DEBUG >> RTC synced with NTP\n"));
      delay(100);
      return true;
    }
    else {
      DEBUG_OUT(F("Timeout\n"));
      ntp.end();
      delay(100);
    }
  }

  DEBUG_OUT(F("DEBUG >> RTC not synced with NTP\n"));
  DEBUG_OUT(F("DEBUG >> Retry attempts exceeded\n"));
  ntp.end();
  return false;
}

void datetimeStream() {
  ntp.update();
  DateTime time[2]={rtc.now(),ntp.getEpochTime()};

  DEBUG_OUT(F("DEBUG >> "));
  DEBUG_OUT(F("RTC "));
  DEBUG_OUT(time[0].timestamp(DateTime::TIMESTAMP_DATE)); DEBUG_OUT(F(" "));
  DEBUG_OUT(time[0].timestamp(DateTime::TIMESTAMP_TIME)); DEBUG_OUT(F(" | "));
  DEBUG_OUT(F("NTP "));
  DEBUG_OUT(time[1].timestamp(DateTime::TIMESTAMP_DATE)); DEBUG_OUT(F(" "));
  DEBUG_OUT(time[1].timestamp(DateTime::TIMESTAMP_TIME)); DEBUG_OUT(F("\n"));
}

void heartbeat(uint8_t n) {
  //Blink indicator LED for n-times
  while(n>0) {
    digitalWrite(onboardLed,LOW);
    delay(10);
    digitalWrite(onboardLed,HIGH);
    delay(100);
    n--;
  }
}

// End of File [SENTSOR]
