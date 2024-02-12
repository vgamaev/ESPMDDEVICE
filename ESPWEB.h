#ifndef ESPWEB_h
#define ESPWEB_h

#include <ESP8266WebServer.h>
#include "ESPEEPROM.h"
#include "LAMP.h"
#include "ESPIR.h"
#include "ESPWIFI.h"
#include "ESPMDDEVICE.H"
#include "KARNIZ.h"
#include "ENERGOMERA.h"

extern String VersionCode;

extern int ErrCoutEnergo;

extern String tapeMatrix;
extern int MatrixCounter;

extern String ResiverCode;
extern String TransmiterCode;

extern unsigned long code433;

extern int adcValue;

extern  float tempDHT;
extern  float humDHT;
extern  float hicDHT;

extern ESP8266WebServer server; // веб сервер

bool WebAuth();

// функция для главной страници
void handleRoot();

// Находим все точки доступа и записываем их названия в буфер вэб страници
void WIFIScan(String & temp);

// Раббираем ответ от ВЭБ страници конфигурвции.
void WebParser();

// Раббираем ответ от ВЭБ страници кнопок.
void WebParseButton(); 

//Обрабатываем ВЕБ запросы
void handleLedMatrix(); 

// функция для страници настройки устройства
void handleSetup();

// функция для главной страници.
void handleRoot();

// функция для недействительных запросов
void handleNotFound();

#endif
