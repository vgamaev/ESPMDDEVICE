#ifndef ESPWIFI_h
#define ESPWIFI_h

#include <ESP8266WiFi.h>
#include "ESPEEPROM.h"

// Функция конвертирует IP адрес в строку
void IPAddressToString(IPAddress ip, String &StrIP);

void EnableAP();

void ConectWIFI();

#endif
