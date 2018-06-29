#ifndef DHT22_h
#define DHT22_h

#include "ESPMDDEVICE.H"

#ifdef DHT22

#include <ESP8266HTTPClient.h>
#include "ESPEEPROM.h"
#include "DHT.h"

extern HTTPClient http; // веб клиент

#define DHTPIN 12     // what digital pin we're connected to

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

extern  float tempDHT;
extern  float humDHT;
extern  float tempDHTOld;
extern  float humDHTOld;
extern  float hicDHT;

void dhtInit();
void dhtRead();

#endif
#endif
