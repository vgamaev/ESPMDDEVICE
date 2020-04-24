#ifndef ADC_h
#define ADC_h

#include "ESPMDDEVICE.H"

#ifdef ADC

#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include "ESPEEPROM.h"

extern HTTPClient http; // веб клиент

extern String VersionCode;
extern long   ADCInterval ;
extern String VersionADC ;

extern int adcValue;
extern int adcValueOld;

void adcRead();
void ADCInit();

#endif
#endif
