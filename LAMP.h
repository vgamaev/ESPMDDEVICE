#ifndef LAMP_h
#define LAMP_h

#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include "ESPEEPROM.h"
#include "ESPMDDEVICE.H"
#include "ESPWEB.h"

#ifdef RELAYS_ON

extern ESP8266WebServer server; // веб сервер
extern HTTPClient http; // веб клиент

extern bool web_button_state[];

extern int RelayPin[]; 
extern int lamp_on[];

extern int ButtonPin[]; // "Ловим" выключатель через GPIO0
extern int can_toggle[];
extern int button_state[];
extern bool web_button_state[];

#define RELAY_1 0
#define RELAY_2 1
#define RELAY_3 2

#define BUTTON_1 0
#define BUTTON_2 1
#define BUTTON_3 2

void WebButtonRead(String status, int RelayN);

//Init button state
void web_button_state_init();

// Инециализируем выходы для реле
void RelayInit();

// Обрабатываем нажатие кнопок
void ButtonSwitch();

// Инециализируем входы для кнопок
void ButtonInit();

// Проверяем нажатие кнопок выключателя
void ButtonRead();

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
void sendServer(bool state, int relay_n);

#endif
#endif
