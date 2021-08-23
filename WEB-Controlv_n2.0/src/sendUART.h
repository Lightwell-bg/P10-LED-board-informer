bool sendToLED(String data, char type);

void sendAirTemp(uint32_t per) {
  static uint32_t ms = 0;
  if (millis() - ms < per) return;
  if (!onAirMan) {
      if(myWeather.getWeather(&lang)) {
        airTemp = (myWeather.temp >= 0? "+" + String(myWeather.temp, 1) : String(myWeather.temp, 1));
        timeSendAir = myESPTime.getTimeStr(true);
      }
  }
  else airTemp = airManTemp;
  sendToLED(airTemp, '2'); 
  Serial.print("sendAirTemp: "); Serial.println(airTemp);
  ms = millis();
}

void sendSeaTemp(uint32_t per) {
  static uint32_t ms = 0;
  if (millis() - ms < per) return;
  if (!onSeaMan) {
      if(myWeather.getSeaTemp(seaID.c_str())) {
        seaTemp = myWeather.seaTemp;
        timeSendSea = myESPTime.getTimeStr(true);
      }  
  }
  else seaTemp = seaManTemp; 
  sendToLED(seaTemp, '1');
  Serial.print("sendSeaTemp: "); Serial.println(seaTemp);
  ms = millis();
}

void sendTime(uint32_t per) {
  static uint32_t ms = 0;
  if (millis() - ms < per) return;
  String tn = String(myESPTime.getTimeUNIX());
  sendToLED(tn, '3');
  Serial.print("sendTime: "); Serial.println(tn);
  ms = millis();
}

bool sendToLED(String data, char type) {
  if (type != 's') data = type + data;
  uint8_t sumCRC = 0;  // CRC
  uint8_t strLength = data.length();
  char dataToLED[strLength];
  Serial.print("strLength "); Serial.println(strLength);
  data.toCharArray(dataToLED, strLength+1);
  for (uint8_t i=0; i < strLength; i++) {
    Serial1.write(dataToLED[i]);
    Serial.print("dataToLED[");Serial.print(i);Serial.print("]: "); Serial.print((char)dataToLED[i]); Serial.print("   x"); Serial.println(dataToLED[i],HEX); 
  }
  sumCRC = CRC.crc8t(((uint8_t *)(& dataToLED)), strLength);
  Serial.print("sumCRC x"); Serial.println(sumCRC, HEX);
  Serial1.write(char(sumCRC));
  Serial1.write(';');  
  return 1;
}

