#ifndef LEDMATRIX_h
#define LEDMATRIX_h

#include "ESPMDDEVICE.H"

#ifdef LED_MATRIX

//#include <Arduino.h>
//#include <ESP8266HTTPClient.h>
  
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>
#include <ESP8266WebServer.h>
#include "ESPEEPROM.h"

//extern HTTPClient http; // веб клиент

extern ESP8266WebServer server; // веб сервер

extern int pinCS; // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
extern int numberOfHorizontalDisplays;
extern int numberOfVerticalDisplays;
extern String tape;
extern int wait; // In milliseconds
extern int spacer;
extern int width; // The font width is 5 pixels

extern String ssid1;


//Потдержка русского языка
String utf8rus(String source);

//Инециализируем светодиодные матрици.
void LedMatrixInit();

//Отображение информации на матрице
void LedMatrix();

//Обрабатываем ВЕБ запросы
void handleLedMatrix(); 

#endif
#endif
