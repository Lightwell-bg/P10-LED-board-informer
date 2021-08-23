void softSerialRead() { //Чтение данных от PC
  static uint8_t index;
  static bool flagSysSet;
  static uint8_t sumCRC = 0;  // контрольная сумма
  uint8_t sizeOfRecData = 0; //Число принятых символов для отображения
  //static boolean getStarted; //Старт парсинга от PC
  while (softSerial.available() > 0) {
    if (index > 50) index = 0; //!массив преполняется!!!!!
    wdt_reset();
    byte incomingByte = softSerial.read();        //  ЧИТАЕМ входящий символ
    Serial.print("Recieved serialEvent ");Serial.print((char)incomingByte); Serial.print("   x"); Serial.println(incomingByte,HEX); //****************************************
    //if (getStarted) {                         // если приняли начальный символ (парсинг разрешён)
    if (incomingByte != ';' /*&& incomingByte != 13 && incomingByte != 10*/) {   // если это не пробел И не конец  
          if (incomingByte == '$')  flagSysSet = true; 
          dataFromPC[index] = incomingByte;
          index++;
          //delay(50);
    }
    if (incomingByte == ';') {                // если приняли ; - конец парсинга
       //getStarted = false;
       sizeOfRecData = index;
       Serial.print("sizeOfRecData ");Serial.println(sizeOfRecData); //****************************************
       index = 0;
       sumCRC = CRC.crc8t(((uint8_t *)(& dataFromPC)), sizeOfRecData-1);
       Serial.print("&sumCRC ");Serial.println(sumCRC,HEX); //****************************************
       //Serial.print("dataFromPC[sizeOfRecData-1] ");Serial.println(dataFromPC[sizeOfRecData-1],HEX); //****************************************

       if (sumCRC == dataFromPC[sizeOfRecData-1])  {        // контрольная сумма правильная 
         if (flagSysSet) {
          flagSysSet = false;
          getSysData();
          sumCRC = 0;
          break; //ЧТОБЫ ПЕРЕДАТЬ УПРАВЛЕНИЕ LOOP или так и будем крутиться в WHILE
         }
         else {
          flagSysSet = false;
          getData(sizeOfRecData-1);
          sumCRC = 0;
          break; //ЧТОБЫ ПЕРЕДАТЬ УПРАВЛЕНИЕ LOOP или так и будем крутиться в WHILE
         }              
         sumCRC = 0;
       }
       else {
        sumCRC = 0;
        index = 0;
        flagSysSet = false; 
       }
    } 
  }
}//END Чтение данных от PC и парсинг

// Compute a Dallas Semiconductor 8 bit CRC directly.
// this is much slower, but much smaller, than the lookup table.
//
/*uint8_t crc8(const uint8_t *addr, uint8_t len) {
  uint8_t crc = 0;
  while (len--) {
    uint8_t inbyte = *addr++;
    for (uint8_t i = 8; i; i--) {
      uint8_t mix = (crc ^ inbyte) & 0x01;
      crc >>= 1;
      if (mix) crc ^= 0x8C;
      inbyte >>= 1;
    }
  }
  return crc;
}*/
