#include <Arduino.h>
#include <weatherAP.h>

weatherAP::weatherAP(WiFiClient* client) {
    _client = client;
}

void weatherAP::setWeatherServer(const char* wURL, const char* wAPI, const char* wCityID) {
    _wURL = wURL;
    _wAPI = wAPI;
    _wCityID = wCityID;
}

bool weatherAP::getWeather(const uint8_t* lang) {
    if (WiFi.status() != WL_CONNECTED) { return 0; }
    String wStrURL = String("GET /data/2.5/weather?id=") + String(_wCityID); 
    wStrURL += "&units=metric&appid=" + String(_wAPI);
    switch (*lang) {
        case 0: 
        wStrURL += "&lang=ru";
        break;
        case 1:
        wStrURL += "&lang=bg";
        break;
        case 2:
        wStrURL += "&lang=en";
        break;     
        default:
        wStrURL += "&lang=en";
        break;
    }  
    wStrURL += "\r\nHost: " +String(_wURL) + "\r\nUser-Agent: ArduinoWiFi/1.1\r\nConnection: close\r\n\r\n";
    //Serial.println(wStrURL);
    if (_client->connect(_wURL, 80)) {
        _client->println(wStrURL);
    }
    else {
        Serial.print(F("Connection weather server failed")); Serial.println(_wURL);
        return 0; 
    }
    const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 2*JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(13) + 570;
    DynamicJsonDocument root(capacity);
    String answerWeather = _client->readString();
    //Serial.println(answerWeather);
    DeserializationError error = deserializeJson(root, answerWeather);
    if (error) {
        Serial.print(F("Json parsing failed! ")); Serial.print(F("deserializeJson() failed with code ")); Serial.println(error.c_str());    
        _client->stop();
        return 0; 
    }
    _client->stop(); 
    coord_lon = root["coord"]["lon"];
    coord_lat = root["coord"]["lat"];
    JsonObject weather_0 = root["weather"][0];
    wDescription = weather_0["description"].as<String>();
    wIcon = weather_0["icon"].as<String>();
    JsonObject main = root["main"];
    temp = main["temp"]; 
    feels_like = main["feels_like"];
    humidity = main["humidity"];
    pressure = main["pressure"];
    pressure_mm = pressure/1.3332239;
    temp_min = main["temp_min"];
    temp_max = main["temp_max"];
    wSpeed = root["wind"]["speed"];
    wDeg = root["wind"]["deg"];
    clouds = root["wind"]["deg"];
    sunrise = root["sys"]["sunrise"];
    sunset = root["sys"]["sunset"];
    lastUpdate = millis();
    return 1;
}

bool weatherAP::getSeaTemp(const char* seaID) {
    if (WiFi.status() != WL_CONNECTED) { return 0; }
    Serial.print("connecting to "); Serial.println(_seaURL);
    String wStrURL = String("GET /en/i/") + seaID; 
    wStrURL += "/c/160x86/ HTTP/1.1";

    //wStrURL += "\r\nHost: " + WSea_URL + "\r\nUser-Agent: ArduinoWiFi/1.1\r\nConnection: close\r\n\r\n";
    wStrURL += "\r\nHost: " + String(_seaURL) + "\r\nUser-Agent: Mozilla/5.0 (Windows NT 6.3; WOW64; rv:36.0) Gecko/20100101 Firefox/36.0\r\nConnection: close\r\n\r\n";
    //Serial.println(wStrURL);  
    if (_client->connect(_seaURL, 80)) {
        _client->println(wStrURL);
    }
    else {
        Serial.println("Weather server connection failed");
        return 0;
    }
    String response = "";
    unsigned startTime = millis();
    delay (200);
    while (!_client->available() < 1 && ((millis()-startTime) < 5000)) {
            delay (5);
    }
    
    while (_client->available()) { // Get response from server
        char charIn = _client->read(); // Read a char from the buffer.
        response += charIn;     // Append the char to the string response.
    }
    _client->stop();
    uint16_t firstInt = response.indexOf("temp\">");
    uint16_t secondInt = response.indexOf("&deg",firstInt);
    String temp = response.substring(firstInt+6, secondInt);
    if (temp != "")  {
        if(temp.indexOf("-")==-1) seaTemp = "+" + temp;
        else seaTemp = temp;
        lastSeaUpdate = millis();
        return 1;
    }
    else {
        return 0;
    }
}
/*weatherDataStruct weatherAP::getWeatherData(void) {
    return _wData;
}*/