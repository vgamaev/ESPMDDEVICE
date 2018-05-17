#ifndef ESPWEB_h
#define ESPWEB_h

#include <ESP8266WebServer.h>
#include "ESPEEPROM.h"
#include "LAMP.h"
#include "ESPWIFI.h"
#include "ESPMDDEVICE.H"

extern String tapeMatrix;
extern int MatrixCounter;

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

// Раббираем ответ от ВЭБ страници информера.
void WebParserinformer();

// функция для страници настройки устройства
void handleSetup();

// функция для главной страници.
void handleRoot();

// функция для недействительных запросов
void handleNotFound();

#endif
