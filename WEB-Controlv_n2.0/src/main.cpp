#include <Arduino.h>
#include "config.h"
#include "configjson.h"
#include "ssdp.h"
#include "sendUART.h"
#include "serverhttp.h"
#include "updFirmware.h"

void setup() {
  Serial.begin(115200);
  Serial1.begin(2400);
  Serial1.write(';');
  SPIFFS.begin(); Serial.println(F("Start FS"));   //Run FS
  loadConfig(); Serial.println(F("FileConfig"));
  if(myWIFI.begin(ssid.c_str(), password.c_str(), SSDP_Name.c_str(), ssidAP.c_str(), passwordAP.c_str(), apIP.c_str())) {
    Serial.println(F("Start WIFI"));  //Run WIFI
  }
  Serial.println(myWIFI.getDevStatusIP());
  if (WiFi.status() == WL_CONNECTED)  {
    SSDP_Name = myWIFI.getNameSSDP();
    SSDP_init(); Serial.println(F("Start SSDP"));   //Run SSDP 
  }
  myESPTime.begin(timezone, isDayLightSaving, sNtpServerName, sNtpServerName2, sNtpServerName3, useRTC, updateRTCfromNTP); Serial.println(F("Start Time"));
  initUpdFirmware();
  initHTTP(); Serial.println(F("Start HTTPServer"));   //Run HTTP server
  myWeather.setWeatherServer(weatherHost.c_str(), weatherKey.c_str(), cityID.c_str());
  sendToLED(myWIFI.getDevStatusIP(), '0'); 
  delay(5000);
  if (!onSeaMan) {
      if(myWeather.getSeaTemp(seaID.c_str())) {
        seaTemp = myWeather.seaTemp;
        timeSendSea = myESPTime.getTimeStr(true);
      }  
      else {
        seaTemp = "n/a";
      }
  }
  else seaTemp = seaManTemp; 
  sendToLED(seaTemp, '1');
  Serial.print("sendSeaTemp: "); Serial.println(seaTemp);
  delay(5000);
  if (!onAirMan) {
      if(myWeather.getWeather(&lang)) {
        airTemp = (myWeather.temp >= 0? "+" + String(myWeather.temp, 1) : String(myWeather.temp, 1));
        timeSendAir = myESPTime.getTimeStr(true);
      }
      else {
        airTemp = "n/a";
      }
  }
  else airTemp = airManTemp;
  sendToLED(airTemp, '2');
  Serial.print("sendAirTemp: "); Serial.println(airTemp); 
  PERIOD_AIR_SEND = updInter*1000*60; PERIOD_SEA_SEND = updInter*1000*60 + 10000;
}

void loop() {
  //static uint32_t sCount = 0, wCount = 0;
  HTTP.handleClient();
  sendAirTemp(PERIOD_AIR_SEND);
  sendSeaTemp(PERIOD_SEA_SEND);
  if (onClock) {
    sendTime(PERIOD_TIME_SEND);
  }
  /*if (millis()-wCount>90000) {
    if(myWeather.getWeather(&lang)) {
        Serial.print("wDescription "); Serial.println(myWeather.wDescription);
        Serial.print("temp "); Serial.println(myWeather.temp);
        Serial.print("feels_like "); Serial.println(myWeather.feels_like);
        Serial.print("sunrise "); Serial.println(myWeather.sunrise);
        Serial.print("sunset "); Serial.println(myWeather.sunset);
        Serial.print("lastUpdate "); Serial.println(myWeather.lastUpdate);
        wCount = millis();
    }
  }
  if (millis()-sCount>120000) {
    if(myWeather.getSeaTemp(seaID.c_str())) {
        Serial.print("seaTemp "); Serial.println(myWeather.seaTemp);
        Serial.print("lastSeaUpdate "); Serial.println(myWeather.lastSeaUpdate);
        sCount = millis();
    }
  }*/
  delay(1);
}