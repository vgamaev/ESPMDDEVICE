#ifndef ESPWIFI_h
#define ESPWIFI_h

#include <ESP8266WiFi.h>
#include "ESPEEPROM.h"
#include "ESPMDDEVICE.H"

extern long WiFiCheckinterval;  //Интервал проверки WiFi потключения
extern int WIFI_led;          // Светодиод на выклчателе GPIO13

extern int WIWI_Connect;

extern String ssid1;
extern const char *password1;

// Функция конвертирует IP адрес в строку
void IPAddressToString(IPAddress ip, String &StrIP);

void EnableAP();

void ConectWIFI();

//Индикация потключения по wifi
void WiFiLedStatus();

#endif
