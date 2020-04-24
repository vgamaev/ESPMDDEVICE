#ifndef LEDMATRIX_h
#define LEDMATRIX_h

#include "ESPMDDEVICE.H"

#ifdef LED_MATRIX
  
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>
#include <ESP8266WebServer.h>
#include "ESPEEPROM.h"

extern unsigned long StrToULong(char *str);
extern ESP8266WebServer server; // веб сервер

extern String VersionCode;
extern String VersionLedMatrix ;

extern int pinCS; // Попробуйте пины. DIN -> GPIO13 (MOSI) SCK -> GPIO14 (SCK) CS -> GPIO15 
extern int numberOfHorizontalDisplays;
extern int numberOfVerticalDisplays;
extern String tapeMatrix;
extern String tape;
extern int wait; // In milliseconds
extern int spacer;
extern int width; // The font width is 5 pixels
extern int MatrixOFF;
extern int MatrixCounter;
extern String ssid1;

//Потдержка русского языка
String utf8rus(String source);

//Инециализируем светодиодные матрици.
void LedMatrixInit();

//Отображение информации на матрице
void LedMatrix();

// Раббираем ответ от ВЭБ страници информера.
void WebParserinformer();

#endif
#endif
