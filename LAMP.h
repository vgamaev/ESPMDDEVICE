#ifndef LAMP_h
#define LAMP_h

#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include "ESPEEPROM.h"
#include "ESPMDDEVICE.H"

extern ESP8266WebServer server; // веб сервер
extern HTTPClient http; // веб клиент

extern int RelayPin[]; 
extern int button; // "Ловим" выключатель через GPIO0

extern int lamp_on[];

#define RELAY_1 0
#define RELAY_2 1
#define RELAY_1 3

// Инециализируем выходы для реле
void RelayInit();

// Включаем лампу
void turnOnLamp(int nomer);

// Выключаем лампу
void turnOffLamp(int nomer);

// Изменяем состояние лампы
void toggleLamp(int nomer);

// Получаем от сервера команду включить
void handleOn();

// Получаем от сервера команду выключить
void handleOff();

// Получаем от сервера команды управления реле
void handleRelay();

// Отправляем серверу MojorDomo события вкл./выкл.
void sendServer(bool state);

#endif
