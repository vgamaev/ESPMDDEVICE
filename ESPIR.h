#ifndef ESPIR_h
#define ESPIR_h

#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include "ESPEEPROM.h"

extern int RECV_PIN; //an IR detector/demodulatord is connected to GPIO pin 2
extern int SEND_PIN; //an IR led is connected to GPIO pin 0

extern ESP8266WebServer server; // веб сервер
extern HTTPClient http; // веб клиент

unsigned long StrToULong(char *str);
void StartIR();
void IRResiver();
void IRTransmiter(unsigned long SendIRCode);
void handleIR();

#endif
