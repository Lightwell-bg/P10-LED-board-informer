#include "config.h"

void setup() {
  Serial.begin(115200);    // Debugging only
  randomSeed(analogRead(0));
  wdt_disable();
  valSpeedCom = 2400;
  EEPROM.put(6, valSpeedCom);
  EEPROM.get(6, valSpeedCom); 
  if  (valSpeedCom != 1200 && valSpeedCom != 2400 && valSpeedCom != 4800) {
    valSpeedCom = 2400;  
  }
  softSerial.begin(valSpeedCom);
  valBrightness = EEPROM.read(1);
  Serial.print("valBrightness ");Serial.println(valBrightness); //****************************************
  Serial.print("valSpeedCom ");Serial.println(valSpeedCom); //****************************************
  EEPROM.get(6, valSpeedCom);
  Serial.print("valSpeedCom from EEPROM ");Serial.println(valSpeedCom); //****************************************
  dmodefrom = EEPROM.read(2);
  Serial.print("dmodefrom ");Serial.println(dmodefrom); //****************************************
  valBrightnessN = EEPROM.read(3);
  Serial.print("valBrightnessN ");Serial.println(valBrightnessN); //****************************************
  dmodeto = EEPROM.read(4);
  Serial.print("dmodeto ");Serial.println(dmodeto); //****************************************  
  dmd.setBrightness(valBrightness);
  dmd.begin();
  dmd.clearScreen();
  dmd.selectFont(Droid_Sans_12);
  dmd.drawString(2, 3, logo); 
  delay(500); 
  dmd.clearScreen();
  dmd.drawString(2, 3, String(valBrightness));
  delay(500); 
  dmd.clearScreen();
  dmd.drawString(2, 3, String(valSpeedCom));
  delay(500); 
  dmd.clearScreen();             
  Serial.println(F("Start!"));
  wdt_enable (WDTO_4S);  
}
//const char *MESSAGE = "ss~!@@#$%^&*()_+?><.,";
void loop() {
  static uint8_t sMode=0, oldsMode = 1;
  static uint32_t tCount = 0;
  static bool chMode = true;
  wdt_reset();
  softSerialRead();
  time_t tn = now();  uint8_t nowhour = hour(tn); 
  if (nowhour >= dmodefrom && nowhour < dmodeto) dmd.setBrightness(valBrightness); else dmd.setBrightness(valBrightnessN);
  if (sTemp == "" && aTemp == "" && timeStatus() == timeNotSet) {
    showFistInfo();
  }
  if (sMode != oldsMode) {Serial.print(F("Mode ")); Serial.println(sMode); oldsMode = sMode;}
  if (millis()-tCount > intShowData) {
    sMode++;
    oldHour = 25, oldMinute = 65;
    dmd.clearScreen();
    chMode = true;
    tCount = millis();
  }
  if (sMode > maxMode) {sMode = 1;}

  /*if (millis()-showTime > 1000*5 || noData) {
    (showStep>=showNum?showStep=1:showStep++);
    oldHour = 25, oldMinute = 65;
    dmd.clearScreen(); 
    noData = false;
    showTime = millis(); 
  }*/

  if (sMode == 1) { //show Time
    if ((timeStatus() != timeNotSet) && (timeStatus() != timeNeedsSync)) {
      showTime();
    }
    else sMode++;
  }

  if (sMode == 2 && chMode) { //show sea temp
    if (sTemp != "") {
      showSeaTemp();
      chMode = false;  
    }
    else sMode++;
  }

  if (sMode==3 && chMode) { //show air temp
    if (aTemp != "") {
      showAirTemp();
      chMode = false;  
    }
    else sMode++;
  }
}
