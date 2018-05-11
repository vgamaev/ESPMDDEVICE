#ifndef LEDMATRIX_h
#define LEDMATRIX_h

#include "LEDMATRIX.h"

#ifdef LED_MATRIX

//#include <Arduino.h>
//#include <ESP8266HTTPClient.h>
//#include "ESPEEPROM.h"

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

//extern HTTPClient http; // веб клиент

int pinCS = 15; // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
int numberOfHorizontalDisplays = 4;
int numberOfVerticalDisplays = 1;

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

String tape = "Gamaev Vlad Гамаев Влад";
int wait = 80; // In milliseconds

int spacer = 1;
int width = 5 + spacer; // The font width is 5 pixels

//Потдержка русского языка
String utf8rus(String source);

//Инециализируем светодиодные матрици.
void LedMatrixInit();

//Отображение информации на матрице
void LedMatrix();

#endif
#endif
