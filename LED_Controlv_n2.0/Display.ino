void showFistInfo() {
    dmd.setBrightness(255);
    const char *next = MESSAGE;
    dmd.selectFont(Droid_Sans_12);
    while(*next) {
      wdt_reset();
      Serial.print(*next);
      box2.print(*next);
      delay(200);
      next++;
    }
    Serial.println();
    const char *nextip = sIP.c_str();
    while(*nextip) {
      wdt_reset();
      Serial.print(*nextip);
      box2.print(*nextip);
      delay(200);
      nextip++;
    }
    Serial.println();    
}

void showSeaTemp() {
  dmd.selectFont(Arial_Black_1016);
  dmd.clearScreen();  
  box1.clear();
  //dmd.drawString(1, 0, recievedMsg);
  //box1.scrollX(1);
  box1.print("Sea");
  for (byte i=0; i < 16; i++) {
    box1.scrollY(-1);
    delay(5);  
  }
  //box1.clear();
  //dmd.selectFont(BigFont1016);
  Serial.print("Sea: ");Serial.println(sTemp);
  dmd.drawString(5, 1, sTemp + "\x82"+"C");
  //delay(3000);
}

void showAirTemp() {
  dmd.selectFont(Arial_Black_1016);
  dmd.clearScreen();
  box1.clear();  
  box1.print("Air");
  for (byte i=0; i < 16; i++) {
    box1.scrollY(-1);
    delay(5);  
  }
  //dmd.selectFont(BigFont1016);
  Serial.print("Air: "); Serial.println(aTemp);
  dmd.drawString(5, 1, aTemp + "\x81"+"C");
  //delay(3000);    
}

void showTime() { 
  uint8_t now_hour, now_minute, now_second;
  static time_t prevDisplay; // предыдущее показание часов 
  static String strTime;
  static bool Dot = true;  //Dot state
  static unsigned long lastTimeDOT;
  dmd.selectFont(Arial_Black_1016);
  if (now() != prevDisplay) {  // обновляем дисплей только если время поменялось
    prevDisplay = now();
    now_hour=hour();
    now_minute=minute();
    now_second =second();
    strTime = String(now_hour) + ":" + String(now_minute) + ":" + String(now_second);
    //Serial.print("TimeToDisplay(): "); Serial.println(strTime);                
  }
    if (now_hour != oldHour) {
      //Serial.println("now_hour1"); 
      if (now_hour < 10) {
        boxH_8.clear(); 
        boxH_8.print(String(now_hour));         
      }
      else if (now_hour == 11) {
        boxH_12.clear(); 
        boxH_12.print(now_hour);         
      }                
      else if (now_hour == 21 || (now_hour>9 && now_hour<20 && now_hour!=11)) {
        boxH_14.clear(); 
        boxH_14.print(now_hour);         
      }        
      else {
        boxH_16.clear(); 
        boxH_16.print(now_hour);         
      }
      oldHour = now_hour;
    }
    //Serial.print("Dot: "); Serial.println(Dot);
    if (millis() - lastTimeDOT > 500)  {
      if (Dot) {
        boxDOT.clear();
      }
      else {
        //boxDOT.print("\x83"); 
        boxDOT.print(":"); 
      }
      Dot = !Dot;
      lastTimeDOT = millis();    
      //Serial.print("time1 "); Serial.println(strTime);
    }
  
    if (now_minute != oldMinute) {
      boxM.clear();
      if (now_minute < 10) {
        boxM.print("0"); boxM.println(now_minute);  
      }
      else {boxM.println(now_minute);}
      oldMinute = now_minute;
    } 
}
