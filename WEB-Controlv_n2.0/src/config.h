#ifndef GLOBAL_H
#define GLOBAL_H
const String modelName = "LWSeaTemp";
const String nVersion = "v2.0";

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h> 
#include <ESP8266HTTPClient.h>  
#include <WiFiClientSecure.h>
#include <ESP8266SSDP.h> 
#include <Updater.h>//for update firmware and SPIFFS
#include <FS.h>  
#include <ArduinoJson.h>        //https://github.com/bblanchon/ArduinoJson.git
#include "RTClib.h" //https://github.com/adafruit/RTClib
#include "ESPTimeFunc.h"
#include "NetCrtESP.h"
#include "weatherAP.h"
#include "CRC816.h"

#include "P_js.h"
#include "P_css.h"
#include "P_index.h"
#include "P_wifi.h"
#include "P_time.h"
#include "P_help.h"

bool useRTC = false; //get time RTC

WiFiClient ESPclient;
ESP8266WebServer HTTP; 
NetCrtESP myWIFI;
ESPTimeFunc myESPTime(useRTC);
weatherAP myWeather(&ESPclient);

String cVersion = modelName + nVersion;

String fileConfigPath = "/myConfig.json"; //File for config
String jsonConfig = "{}";

// wifi
String ssid = "SSIDWiFi";
String password = "passwordWiFi";
String ssidAP = "LWSeaTemp";   // SSID AP точки доступа
String passwordAP = ""; // пароль точки доступа
String SSDP_Name = "LWSeaTemp"; // Имя SSDP
String apIP = "192.168.4.1";

uint8_t lang = 2; //0-RU, 1-BG, 2 -EN, 3-UA
//Time
//const unsigned long TIME_UPDATE = 1000*60*10; //Интервал обновления времени
int8_t timezone = 2;               // часовой пояс GTM
String sNtpServerName = "us.pool.ntp.org";
const char sNtpServerName2[] = "pool.ntp.org";
const char sNtpServerName3[] = "time.nist.gov";
bool isDayLightSaving = false; //Summer time use
bool updateRTCfromNTP = true; //

//Weather
String weatherHost  = "api.openweathermap.org";
String  weatherKey    = "1*********************e7"; 
String  cityID     = "732770"; // Other city code http://bulk.openweathermap.org/sample/city.list.json.gz
//String seaHost = "worldseatemp.com";
String seaID = "59";

String airTemp = "", seaTemp = "", airManTemp = "", seaManTemp = "";
uint8_t updInter = 10; //for web interface
uint32_t PERIOD_AIR_SEND = updInter*1000*60, PERIOD_SEA_SEND = updInter*1000*60 + 10000;
const uint32_t PERIOD_TIME_SEND = 3600000;
String timeSendAir = "n/a", timeSendSea = "n/a";

//Screen
uint8_t dayModeFrom = 8, dayModeTo = 20; //DAY MODE
uint8_t brightDay = 150, brightNight = 50; //brightness day and night
bool onClock = true;
bool onAirMan = false, onSeaMan = false;


#endif