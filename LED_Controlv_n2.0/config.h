#ifndef GLOBAL_H
#define GLOBAL_H
#include <DMD2.h>
#include <EEPROM.h>
#include <avr/wdt.h> //Interrupt
#include "Arial_Black_1016.h"
#include <fonts/Droid_Sans_12.h>
#include <SoftwareSerial.h>
#include <TimeLib.h> //https://github.com/PaulStoffregen/Time Michael Margolis
#include "CRC816.h"


#define DISPLAYS_WIDE 2
#define DISPLAYS_HIGH 1
#define PIN_OE 9
#define PIN_A 6
#define PIN_B 7
#define PIN_SCK 8
#define PIN_CLK 13
//#define PIN_MOSI_R 11
//#define PIN_MOSI_G 5
#define rxPin 3
#define txPin 4

SPIDMD dmd(DISPLAYS_WIDE, DISPLAYS_HIGH, PIN_OE, PIN_A, PIN_B, PIN_SCK);
DMD_TextBox box1(dmd, 18, 1, 64, 16); //Сдвиг работает только для скроллинга
DMD_TextBox box2(dmd, 0, 3, 64, 16);
  //DMD_TextBox boxH(dmd, 13, 1, 18, 16);
  DMD_TextBox boxH_16(dmd, 11, 1, 19, 16);
  DMD_TextBox boxH_14(dmd, 13, 1, 19, 16); //21,10,12-19
  DMD_TextBox boxH_12(dmd, 15, 1, 19, 16); //11
  DMD_TextBox boxH_8(dmd, 20, 1, 8, 16); //Position for one digit
  DMD_TextBox boxM(dmd, 35, 1, 25, 16);
  DMD_TextBox boxDOT(dmd, 30, 1, 3, 16);
SoftwareSerial softSerial(rxPin, txPin); // RX, TX

uint8_t dataFromPC[50]; //Данные от PC 
char logo[] = "LIGHTWELL";
const char *MESSAGE = "Wait data...  ";
uint8_t valBrightness = 100, valBrightnessN = 10; //Значение яркости (0 - самое яркое) comand - $1200; valBrightness = 200
unsigned long valSpeedCom = 2400; //Значение скорости работы COM-port comand - $3009600; valSpeedCom = 9600 bod MAX 
uint32_t intShowData = 5000;
uint8_t maxMode = 3;
String sTemp="", aTemp="", sIP = "";
uint8_t oldHour = 25, oldMinute = 65;//Старые Значения часов и минут, вынесены сюда чтобы при первом запуске не были равны 0 (тогда при времени 0:00 не срабатывает индикация 
uint8_t dmodefrom = 8, dmodeto = 20; //DAY MODE

void softSerialRead();

#endif
