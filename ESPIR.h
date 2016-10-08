#ifndef ESPIR_h
#define ESPIR_h

#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <ESP8266HTTPClient.h>
#include "ESPEEPROM.h"

extern int RECV_PIN; //an IR detector/demodulatord is connected to GPIO pin 2
extern int SEND_PIN; //an IR led is connected to GPIO pin 0

extern HTTPClient http; // веб клиент

void StartIR();
void IRResiver();
void IRTransmiter();

#endif
