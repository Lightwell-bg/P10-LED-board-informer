void handle_ConfigJSON();
void handle_Set_Ssid();
void handle_Time();
void handle_Time_zone();
void handle_NTPServer();
void handle_TimeNew();
void handle_Ledsetup();
void handle_ManTemp();
void handle_Weather();
void handle_Language();
void handle_Restart();
void handle_resetConfig();

void initHTTP(void) {
    HTTP.onNotFound([]() {(404, "text/plain", "FileNotFound");});
    HTTP.serveStatic("/img/favicon.png", SPIFFS, "/img/favicon.png");
    HTTP.on("/", [](){HTTP.send_P(200, "text/html", P_index);});
    HTTP.on("/index.html", [](){HTTP.send_P(200, "text/html", P_index);}); 
    HTTP.on("/wifi.html", [](){HTTP.send_P(200, "text/html", P_wifi);}); 
    HTTP.on("/time.html", [](){HTTP.send_P(200, "text/html", P_time);});
    HTTP.on("/help.html", [](){HTTP.send_P(200, "text/html", P_help);});
    HTTP.on("/style.css", [](){HTTP.send_P ( 200, "text/css", P_css);});
    HTTP.on("/function.js", [](){HTTP.send_P ( 200, "text/plain", P_js);});
    HTTP.on("/favicon.ico", [](){HTTP.send(200, "image/x-icon", "/img/favicon.png");});
    HTTP.on("/configs.json", handle_ConfigJSON); // create configs.json for sending to WEB interface
    HTTP.on("/ssid", handle_Set_Ssid);     // Set WiFi config and SSDP
    HTTP.on("/lang", handle_Language);
    HTTP.on("/Time", handle_Time);     // Sync Time
    HTTP.on("/TimeZone", handle_Time_zone);    // Set time zone
    HTTP.on("/setntpserver", handle_NTPServer); 
    HTTP.on("/TimeNew", handle_TimeNew);     // Set new time 
    HTTP.on("/led", handle_Ledsetup);
    HTTP.on("/tempman", handle_ManTemp);
    HTTP.on("/weather", handle_Weather);
    HTTP.on("/restart", handle_Restart);   // reset ESP
    HTTP.on("/resetConfig", handle_resetConfig);   
    HTTP.begin();  
}

void handle_ConfigJSON() { 
    struct tm tnow = myESPTime.getTimeStruct();
    srtctIP structIpAp = myWIFI.strToIPArr(apIP.c_str());
    String root = "{}";  
    DynamicJsonDocument jsonDoc(2048);
    DeserializationError error =  deserializeJson(jsonDoc, root);
    if (error) {
        Serial.print(F("deserializeJson() failed with code "));
        Serial.println(error.c_str());
        return;
    }     
    JsonObject json = jsonDoc.as<JsonObject>();    
    json["nVersion"] = nVersion;
    json["modelName"] = modelName;   
    json["ssid"] = myWIFI.getNameSSID();
    json["password"] = myWIFI.getPassSSID();
    json["SSDP"] = myWIFI.getNameSSDP();
    json["ssidAP"] = myWIFI.getNameAPSSID();
    json["passwordAP"] = myWIFI.getPassAPSSID();
    json["ip"] = myWIFI.getDevStatusIP();
    json["ipap1_3"] = String(structIpAp.oct1) + "." + String(structIpAp.oct2) + "." + String(structIpAp.oct3) + ".";
    json["ipap4"] = structIpAp.oct4;
    json["time"] = myESPTime.getTimeStr(true);
    json["date"] = myESPTime.getDateStr();
    json["time_h"] = String(tnow.tm_hour);
    json["time_m"] = String(tnow.tm_min);
    json["time_s"] = String(tnow.tm_sec); 
    json["date_day"] = tnow.tm_mday;
    json["date_month"] = tnow.tm_mon + 1;
    json["date_year"] = tnow.tm_year + 1900;
    json["timezone"] = timezone;
    json["isDayLightSaving"] = (isDayLightSaving?"checked":"");
    json["ntpserver"] = sNtpServerName;
    json["use_sync"] = (useRTC?"":"checked");
    json["airTemp"] = airTemp; json["seaTemp"] = seaTemp;
    json["timeSendAir"] = timeSendAir; json["timeSendSea"] =  timeSendSea;
    json["brightDay"] = brightDay; json["brightNight"] = brightNight;
    json["dayModeFrom"] = dayModeFrom; json["dayModeTo"] = dayModeTo;
    json["onClock"] = (onClock==1?"checked":"");
    json["updInter"] = updInter;
    json["lang"] = (lang==0?"RU":lang==1?"BG":lang==2?"EN":"EN"); 
    json["weatherHost"] = weatherHost;
    json["weatherKey"] = weatherKey;
    json["cityID"] = cityID; 
    json["seaID"] = seaID; 
    json["onAirMan"] = (onAirMan==1?"checked":""); json["airManTemp"] = airManTemp;
    json["onSeaMan"] = (onSeaMan==1?"checked":""); json["seaManTemp"] = seaManTemp;
    root = "";
    serializeJson(json, root);
    HTTP.send(200, "text/json", root);      
}

void handle_Set_Ssid() {
  srtctIP structIpAp = myWIFI.strToIPArr(apIP.c_str());
  ssid = HTTP.arg("ssid").c_str();            
  password = HTTP.arg("password").c_str();   
  ssidAP = HTTP.arg("ssidAP").c_str();        
  passwordAP = HTTP.arg("passwordAP").c_str(); 
  SSDP_Name = HTTP.arg("ssdp").c_str();
  String ipap4 = HTTP.arg("ipap4"); 
  apIP = String(structIpAp.oct1) + "." + String(structIpAp.oct2) + "." + String(structIpAp.oct3) + "." + ipap4;
  myWIFI.setConfigWIFI(ssid.c_str(), password.c_str(), SSDP_Name.c_str(), ssidAP.c_str(), passwordAP.c_str());  
  saveConfig();                      
  Serial.println("Set SSID: " + ssid + ", Set password: " + password + ", Set SSID AP: " + ssidAP + ", Set AP password: " + passwordAP + ", SSDP: " + SSDP_Name);
  HTTP.send(200, "text/plain", "OK");   
}

void handle_Time() {    
    myESPTime.timeSynch();
    time_t tn = myESPTime.getTimeUNIX();
    Serial.print(F("nowTime: ")); Serial.println(tn);
    if (tn != 0) sendToLED(String(tn), '3');  
    HTTP.send(200, "text/plain", "OK");        
}

void handle_Time_zone() {    
    timezone = HTTP.arg("timezone").toInt(); 
    HTTP.arg("isDayLightSaving").toInt()==1 ? isDayLightSaving=true : isDayLightSaving=false;
    myESPTime.setTimeParam(useRTC, timezone, isDayLightSaving, sNtpServerName);
    saveConfig();
    myESPTime.timeSynch();
    Serial.println("NTP Time Zone: " + String(timezone) + ",  isDayLightSaving: " + String(isDayLightSaving));
    HTTP.send(200, "text/html", "OK");        
}

void handle_NTPServer() {
    sNtpServerName = HTTP.arg("ntpserver").c_str(); 
    HTTP.arg("use_sync").toInt()==1?useRTC=false:useRTC=true;
    myESPTime.setTimeParam(useRTC, timezone, isDayLightSaving, sNtpServerName);
    saveConfig();
    myESPTime.timeSynch();
    Serial.println("sNtpServerName: " + sNtpServerName + ", useRTC: " + useRTC);
    HTTP.send(200, "text/html", "OK"); 
}

void handle_TimeNew() {
    struct tm timeman;
    time_t epoch_time;
    uint8_t hour_s = HTTP.arg("time_h").toInt(); 
    uint8_t min_s = HTTP.arg("time_m").toInt();
    uint8_t sec_s = HTTP.arg("time_s").toInt();
    uint8_t mday_s = HTTP.arg("date_day").toInt();
    uint8_t mon_s = HTTP.arg("date_month").toInt();
    uint16_t year_s = HTTP.arg("date_year").toInt(); 
    timeman.tm_hour = hour_s; 
    timeman.tm_min = min_s;
    timeman.tm_sec = sec_s;
    timeman.tm_mday = mday_s;
    timeman.tm_mon = mon_s - 1;
    timeman.tm_year = year_s - 1900; 
    epoch_time = mktime(&timeman);
    printf("Setting time: %s", asctime(&timeman));  
    useRTC = true;
    myESPTime.setTimeParam(useRTC, timezone, isDayLightSaving, sNtpServerName);
    myESPTime.setTimeRTC(epoch_time);
    saveConfig();
    myESPTime.timeSynch();
    HTTP.send(200, "text/html", "OK");  
} 

void handle_Ledsetup() {
  String brightDSend, brightNSend;
  brightDay = HTTP.arg("brightDay").toInt();
  brightNight = HTTP.arg("brightNight").toInt();
  dayModeFrom = HTTP.arg("dayModeFrom").toInt();
  dayModeTo = HTTP.arg("dayModeTo").toInt();
  onClock = HTTP.arg("onClock").toInt();
  updInter = HTTP.arg("updInter").toInt();
  saveConfig();
  PERIOD_AIR_SEND = updInter*1000*60; PERIOD_SEA_SEND = updInter*1000*60 + 10000;
  Serial.print("brightDay ");Serial.println(brightDay);Serial.print("brightNight ");Serial.println(brightNight);
  Serial.print("dayModeFrom ");Serial.println(dayModeFrom);Serial.print("dmodeto ");Serial.println(dayModeTo); 
  Serial.print("onClock ");Serial.println(onClock); 
  if (brightDay < 9) brightDSend = "$100" + String(brightDay);
  else if (brightDay > 9 && brightDay < 100) brightDSend = "$10" + String(brightDay);
  else brightDSend = "$1" + String(brightDay);
  brightDSend += (dayModeFrom < 9 ? "0" + String(dayModeFrom) : String(dayModeFrom));
  Serial.print("brightDSend ");Serial.println(brightDSend); 
  sendToLED(brightDSend, 's');  
  if (brightNight < 9) brightNSend = "$200" + String(brightNight);
  else if (brightNight > 9 && brightNight < 100) brightNSend = "$20" + String(brightNight);
  else brightNSend = "$2" + String(brightNight);
  brightNSend += (dayModeTo < 9 ? "0" + String(dayModeTo) : String(dayModeTo));
  Serial.print("brightNSend ");Serial.println(brightNSend); 
  sendToLED(brightNSend, 's');             
  HTTP.send(200, "text/plain", "OK");   
}

void handle_ManTemp() {
  onAirMan = HTTP.arg("onAirMan").toInt();
  airManTemp = HTTP.arg("airManTemp").c_str();
  airManTemp = (airManTemp.indexOf(" ") ==  -1? airManTemp : "+" + airManTemp.substring(1, 5));
  onSeaMan = HTTP.arg("onSeaMan").toInt();
  seaManTemp = HTTP.arg("seaManTemp").c_str();
  seaManTemp = (seaManTemp.indexOf(" ") == -1 ? seaManTemp : "+" + seaManTemp.substring(1, 5));
  Serial.println("onAirMan: " + String(onAirMan) + ",   airManTemp: " + airManTemp + ",   onSeaMan: " + String(onSeaMan) + ",   seaManTemp: " + seaManTemp);
  saveConfig();
  if (onAirMan) {
    airTemp = airManTemp;
    sendToLED(airTemp, '2');
  }
  else {
    if(myWeather.getWeather(&lang)) {
      airTemp = (myWeather.temp >= 0? "+" + String(myWeather.temp, 1) : String(myWeather.temp, 1));
      sendToLED(airTemp, '2');
    }  
  }
  if (onSeaMan) {
    seaTemp = seaManTemp;
    sendToLED(seaTemp, '1');
  }
  else {
    if(myWeather.getSeaTemp(seaID.c_str())) {
      seaTemp = myWeather.seaTemp;
      sendToLED(seaTemp, '1');
    }  
  }
  HTTP.send(200, "text/plain", "OK");
}

void handle_Weather() {
  weatherHost = HTTP.arg("weatherHost").c_str();
  weatherKey = HTTP.arg("weatherKey").c_str();
  cityID = HTTP.arg("cityID").c_str();
  seaID = HTTP.arg("seaID").c_str();
  Serial.println("Set Weather Server: " + weatherHost + ",   Key: " + weatherKey + ",   City ID: " + cityID + ",   seaID: " + seaID);
  saveConfig();
  if(myWeather.getWeather(&lang)) {
      airTemp = (myWeather.temp >= 0? "+" + String(myWeather.temp,1) : String(myWeather.temp,1));
      sendToLED(airTemp, '2');
  }
  if(myWeather.getSeaTemp(seaID.c_str())) {
    seaTemp = myWeather.seaTemp;
    sendToLED(seaTemp, '1');
  }
  HTTP.send(200, "text/plain", "OK");
}


void handle_Language() {               
  if(HTTP.arg("lang") == "RU" && lang !=0) {
    lang = 0;
  }
  else if(HTTP.arg("lang") == "BG" && lang !=1) {
    lang = 1;
  }
  else if(HTTP.arg("lang") == "EN" && lang !=2) {
    lang = 2;
  }
  else {
    HTTP.send(200, "text/plain", "OK"); return;
  }
  Serial.print("Set lang: ");    Serial.println(HTTP.arg("lang").c_str());
  saveConfig();
  HTTP.send(200, "text/plain", "OK");
}

void handle_Restart() {
  String restart = HTTP.arg("device");       
  if (restart == "ok") {                         
    HTTP.send(200, "text/plain", "Reset OK");
    ESP.restart();                               
  }
  else {                                       
    HTTP.send(200, "text/plain", "No Reset"); 
  }
}

void handle_resetConfig() {
  String restart = HTTP.arg("device");
  if(restart == "ok") {
    //SPIFFS.format();
    SPIFFS.remove("/myconfig.json");
    Serial.println("ESP erase Config file");
    delay(3000);
    HTTP.send(200, "text/plain", "OK");
    delay(3000);
    ESP.restart();
  }
}