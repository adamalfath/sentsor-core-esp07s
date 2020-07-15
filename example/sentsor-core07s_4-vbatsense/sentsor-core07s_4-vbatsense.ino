/* =====================================================================
   __  __      _____  ______  _   _  _______   _____   ____   _____ 
   \ \ \ \    / ____||  ____|| \ | ||__   __| / ____| / __ \ |  __ \    
 __ \ \ \ \  | (___  | |__   |  \| |   | |   | (___  | |  | || |__) |   
 \ \ \ \ \_\  \___ \ |  __|  |     |   | |    \___ \ | |  | ||  _  /    
  \ \ \ \     ____) || |____ | |\  |   | |    ____) || |__| || | \ \    
   \_\ \_\   |_____/ |______||_| \_|   |_|   |_____/  \____/ |_|  \_\   

 Project      : Core Board ESP-07S - Vbat Sense
 Description  : Measure voltage from JST-PH connector/VBAT pin
 Author       : SENTSOR
 Version      : 1.0.0 - Initial Build
 Note         : Connect VBAT with ADC1 or short JP1
 
===================================================================== */

#define DEBUG_OUT(msg) Serial.print(msg)
#define onboardLed 2
#define adcPin A0
//ADC LSB in millivolt
#define ADC_LSB 1000.0F/1024.0F
//Voltage divider ratio
#define VDIV_RATIO 4.8745

#include <ESP8266WiFi.h>

void setup() {
  Serial.begin(9600,SERIAL_8N1);
  delay(500);
  DEBUG_OUT(F("\n"));
  
  pinMode(onboardLed,OUTPUT);
  pinMode(adcPin,INPUT);

  WiFi.mode(WIFI_OFF);
  WiFi.forceSleepBegin();
}

void loop() {
  static uint32_t lastMillis;
  if(millis()-lastMillis>=1000L) {
    lastMillis=millis();
    readVBAT();
    heartbeat(1);
  }
}

void readVBAT() {
  uint16_t adcRaw=analogRead(adcPin);
  float V[2],VBatPct;
  const float VlevelMap[22][2]={{0,0},{0,3270},{5,3610},{10,3690},{15,3710},{20,3730},{25,3750},{30,3770},{35,3790},{40,3800},{45,3820},
                               {50,3840},{55,3850},{60,3870},{65,3910},{70,3950},{75,3980},{80,4020},{85,4080},{90,4110},{95,4150},{100,4200}};

  V[0]=adcRaw*ADC_LSB;
  V[1]=V[0]*VDIV_RATIO;
  for(uint8_t i=1;i<22;i++) {
    if(VlevelMap[i][1]>V[1]) {VBatPct=VlevelMap[i-1][0]; break;}
    else if (i==21) {VBatPct=VlevelMap[21][0];}
  }
  
  DEBUG_OUT(F("VADC0 ")); DEBUG_OUT(V[0]); DEBUG_OUT(F("mV | "));
  DEBUG_OUT(F("VADC1 ")); DEBUG_OUT(V[1]); DEBUG_OUT(F("mV | "));
  DEBUG_OUT(F("LEVEL ")); DEBUG_OUT(VBatPct); DEBUG_OUT(F("%\n"));
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
