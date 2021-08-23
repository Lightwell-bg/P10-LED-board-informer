void getData(uint8_t countResSym) {
  String recievedMsg;
  for (byte i=1; i < countResSym; i++) {  
    recievedMsg += (char)dataFromPC[i]; 
    Serial.print("dataFromPC["); Serial.print(i);Serial.print("]");Serial.println((char)dataFromPC[i]); //******************************************
  }
  Serial.println(dataFromPC[0]);  
  if (dataFromPC[0]-'0' == 1) { //temp of sea
    sTemp = recievedMsg;
    Serial.println(sTemp);
  } 
  if (dataFromPC[0]-'0' == 2) { //temp of air
    aTemp = recievedMsg;  
    Serial.println(aTemp);   
  }
  if (dataFromPC[0]-'0' == 3) { //Time
    time_t gotTime = recievedMsg.toInt();
    setTime(gotTime);
    Serial.print("ITime gotTime: "); Serial.println(gotTime);
    time_t tn = now();
    String Time;
    Time = String(hour(tn))+":"+ (minute(tn) < 10 ? "0"+String(minute(tn)) : String(minute(tn)));
    Serial.println("GetTime() "+Time);
  }  
  if (dataFromPC[0]-'0' == 0) { //IP
    sIP = recievedMsg;
    Serial.println(sIP);
  }   
}

void getSysData() {
  switch (dataFromPC[1]-'0') {//Преобразуем команду в число
    case 1: //Установка яркости
      valBrightness  = (dataFromPC[2]-'0')*100 + (dataFromPC[3]-'0')*10 + (dataFromPC[4]-'0');
      EEPROM.write(1, (valBrightness)); //write to 1 val brightness
      dmd.setBrightness(valBrightness);
      dmd.clearScreen(); 
      dmd.selectFont(Droid_Sans_12);
      dmd.drawString(2, 3, String(valBrightness));
      delay(500); 
      dmd.clearScreen(); 
      Serial.print("valBrightness ");Serial.println(valBrightness); //****************************************
      dmodefrom = (dataFromPC[5]-'0')*10 + (dataFromPC[6]-'0');
      EEPROM.write(2, (dmodefrom));
      Serial.print("dmodefrom ");Serial.println(dmodefrom); //****************************************
    break;
    case 2: //Установка яркости night
      valBrightnessN  = (dataFromPC[2]-'0')*100 + (dataFromPC[3]-'0')*10 + (dataFromPC[4]-'0');
      EEPROM.write(3, (valBrightnessN)); //write to 1 val brightness
      //dmd.setBrightness(valBrightnessN);
      dmd.clearScreen(); 
      dmd.selectFont(Droid_Sans_12);
      dmd.drawString(2, 3, String(valBrightnessN));
      delay(500); 
      dmd.clearScreen(); 
      Serial.print("valBrightnessN ");Serial.println(valBrightnessN); //****************************************
      dmodeto = (dataFromPC[5]-'0')*10 + (dataFromPC[6]-'0');
      EEPROM.write(4, (dmodeto));
      Serial.print("dmodeto ");Serial.println(dmodeto); //****************************************
    break;    
    /*case 2: //скорости порта
      valSpeedCom  = (dataFromPC[2]-'0')*100000 + (dataFromPC[3]-'0')*10000 + (dataFromPC[4]-'0')*1000 + (dataFromPC[5]-'0')*100 + (dataFromPC[6]-'0')*10 + (dataFromPC[7]-'0');
      //EEPROM.update(4, valSpeedCom);
      EEPROM.put(4, valSpeedCom);
      softSerial.begin(valSpeedCom); // скорость 9600 38400
      dmd.clearScreen(); 
      dmd.selectFont(Droid_Sans_12);
      dmd.drawString(2, 3, String(valSpeedCom));
      delay(500); 
      dmd.clearScreen(); 
      Serial.print("valSpeedCom ");Serial.println(valSpeedCom); //****************************************
    break; */               
    default:
    break;             
  }   
}
