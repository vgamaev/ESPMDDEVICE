#ifndef WEBUPDATE_h
#define WEBUPDATE_h

#include "ESPMDDEVICE.H"

#ifdef WEBUPDATE

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "ESPWEB.h"

extern String VersionCode;

extern const char* serverIndex;

void handleWebUpdate();
void handleUpdate1();
void handleUpdate2();

#endif
#endif
