#ifndef RF433MHZ_h
#define RF433MHZ_h

#include "ESPMDDEVICE.H"

#ifdef RF433MHZ

#include <Arduino.h>
#include <RCSwitch.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include "ESPEEPROM.h"

void 433Resiver();

void Start433();

#endif
#endif
