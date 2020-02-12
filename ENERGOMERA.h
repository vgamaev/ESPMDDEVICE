#ifndef ENERGOMERA_h
#define ENERGOMERA_h

#include "ESPMDDEVICE.H"

#ifdef ENERGOMERA
  #include <Arduino.h>
  #include <IRremoteESP8266.h>
  #include <ESP8266WebServer.h>
  #include <ESP8266HTTPClient.h>
  #include "ESPEEPROM.h"

  extern ESP8266WebServer server; // веб сервер
  extern HTTPClient http; // веб клиент


#endif
#endif
