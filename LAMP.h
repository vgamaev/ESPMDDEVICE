#ifndef LAMP_h
#define LAMP_h

#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include "ESPEEPROM.h"

extern ESP8266WebServer server; // веб сервер
extern HTTPClient http; // веб клиент

extern int lamp; // Управляем реле через GPIO2
extern int button; // "Ловим" выключатель через GPIO0

extern bool lamp_on;

// Включаем лампу
void turnOnLamp(int pinlamp);

// Выключаем лампу
void turnOffLamp(int pinlamp);

// Изменяем состояние лампы
void toggleLamp(int pinlamp);

// Получаем от сервера команду включить
void handleOn();

// Получаем от сервера команду выключить
void handleOff();

// Отправляем серверу MojorDomo события вкл./выкл.
void sendServer(bool state);

#endif
