bool saveConfig();

bool loadConfig() {
    File configFile = SPIFFS.open(fileConfigPath, "r");  
    if (!configFile) {  // not found
        Serial.println(F("Failed to open config file"));
        saveConfig();   //  create file
        configFile.close();
        return false;
    }
    size_t size = configFile.size();   // myconfig.json must be less 2048 byte
    if (size > 2048) {  
        Serial.println(F("Config file size is too large"));
        configFile.close();
        return false;
    }
    jsonConfig = configFile.readString(); // load config 
    configFile.close();
    DynamicJsonDocument jsonDoc(5096); //4096
    DeserializationError error = deserializeJson(jsonDoc, jsonConfig);
    if (error) {
        Serial.print(F("deserializeJson() failed with code "));
        Serial.println(error.c_str());
        return false;
    }   
    JsonObject root = jsonDoc.as<JsonObject>();
    lang = root["lang"];
    timezone = root["timezone"];               
    isDayLightSaving = root["isDayLightSaving"];
    sNtpServerName = root["ntp_server"].as<String>();
    useRTC = root["useRTC"];
    apIP = root["ipap"].as<String>();
    weatherHost = root["weatherHost"].as<String>();
    weatherKey = root["weatherKey"].as<String>();
    cityID = root["cityID"].as<String>();
    seaID = root["seaID"].as<String>();
    onAirMan = root["onAirMan"]; airManTemp = root["airManTemp"].as<String>();
    onSeaMan = root["onSeaMan"]; seaManTemp = root["seaManTemp"].as<String>();  
    brightDay = root["brightDay"]; brightNight = root["brightNight"];
    dayModeFrom = root["dayModeFrom"]; dayModeTo = root["dayModeTo"];
    onClock = root["onClock"]; 
    updInter = root["updInter"]; 
    onAirMan = root["onAirMan"]; airManTemp = root["airManTemp"].as<String>();
    onSeaMan = root["onSeaMan"]; seaManTemp = root["seaManTemp"].as<String>();  
    return true;
}

// Write to myconfig.json
bool saveConfig() {
    DynamicJsonDocument jsonDoc(5096);//4096
    DeserializationError error = deserializeJson(jsonDoc, jsonConfig);
    if (error) {
        Serial.print(F("deserializeJson() failed with code "));
        Serial.println(error.c_str());
        return false;
    }     
    JsonObject json = jsonDoc.as<JsonObject>(); 
    json["lang"] = lang; 
    json["timezone"] = timezone;
    json["isDayLightSaving"] = isDayLightSaving;
    json["ntp_server"] = sNtpServerName;
    json["useRTC"] = useRTC;
    json["ipap"] = apIP;
    json["weatherHost"] = weatherHost;
    json["weatherKey"] = weatherKey;
    json["cityID"] = cityID;
    json["seaID"] = seaID;
    json["onAirMan"] = onAirMan; json["airManTemp"] = airManTemp;
    json["onSeaMan"] = onSeaMan; json["seaManTemp"] = seaManTemp;
    json["brightDay"] = brightDay; json["brightNight"] = brightNight;
    json["dayModeFrom"] = dayModeFrom; json["dayModeTo"] = dayModeTo;
    json["onClock"] = onClock;
    json["updInter"] = updInter;
    json["onAirMan"] = onAirMan; json["airManTemp"] = airManTemp;
    json["onSeaMan"] = onSeaMan; json["seaManTemp"] = seaManTemp;
    serializeJson(json, jsonConfig);
    File configFile = SPIFFS.open(fileConfigPath, "w");
    if (!configFile) {
        Serial.println(F("Failed to open config file for writing"));
        configFile.close();
        return false;
    }
    serializeJson(json, configFile);
    configFile.close();
    return true;
}