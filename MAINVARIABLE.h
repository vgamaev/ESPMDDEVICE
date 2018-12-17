/* В этом файле собраны переменые при помощи которых можно сконфигурировать например пины, тайминги и т.п */

#include "ESPMDDEVICE.H"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266mDNS.h>
#include "ESPEEPROM.h"
#include "ESPWIFI.h"
#include "ESPWEB.h"
#include "WEBUPDATE.h"

String VersionCode = "2.00";

#ifdef RF433MHZ
    #include "RF433MHZ.h"
unsigned long code433 =0;
#endif

//==============================================
#ifdef ADC
  #include "ADC.h"
  int adcValue = 0;
  int adcValueOld = 0;
#endif

#ifdef IR_RESIVER
//=== IR Resiver ==============================
  #include "ESPIR.h"
  int RECV_PIN = 5; //an IR detector/demodulatord is connected to GPIO pin 2
  int SEND_PIN = 15; //an IR led is connected to GPIO pin 0
  String ResiverCode = "0";
  String TransmiterCode = "0";
#endif


#ifdef RELAYS_ON//==== WIFI SWITCH =============================
  #include "LAMP.h"
  int RelayPin[MAX_RELAY];
  int lamp_on[MAX_RELAY];
  int ButtonPin[MAX_BUTTON];
  int can_toggle[MAX_BUTTON];
  int button_state[MAX_BUTTON];
  bool web_button_state[MAX_RELAY];
#endif

#ifdef LED_MATRIX
  #include "LEDMATRIX.h"
  int pinCS = 15;                           // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
  int numberOfHorizontalDisplays = 5;       // число матриц 8x8 MAX7219по горизонтали
  int numberOfVerticalDisplays = 1;         // Число матриц по вертикали
  String tapeMatrix;                        // Буфер для принятия строки
  String tape;                              // Буфер для отображения строки
  int wait = 80;                            // In milliseconds
  int spacer = 1;
  int width = 5 + spacer;                   // The font width is 5 pixels
  int MatrixOFF = 0 ;
  int MatrixCounter = 0;                    // Счетчик дляотображения бегущей строки
#endif

//==============================================
#ifdef DHT22
  #include "DHT22.h"
  float tempDHT = 0;
  float humDHT = 0;
  float tempDHTOld = 0;
  float humDHTOld = 0;
  float hicDHT = 0;
#endif

//======================= KARNIZ =================================================
#ifdef KARNIZ
  #include "KARNIZ.h"
  //int ENA = 14;
  int IN1 = 16;
  int IN2 = 14;
  int KarnizMotorState = 0;
  int KarnizMotorCommand = 0;
  int KarnizMotorDelay =0;
  long KarnizMotorStartMillis =0;
  
#endif
//=======================Светодиод WIFI=========================================
long WiFiCheckinterval = 1000; //Интервал проверки WiFi потключения
int WIWI_Connect=0;

//#ifdef WIFI_LED
  int WIFI_led = 13;             // Светодиод на выклчателе GPIO13
//#endif

String ssid1;
const char *password1 = "66666666";

ESP8266WebServer server (80) ; // веб сервер
HTTPClient http; // веб клиент

unsigned long StrToULong(char *str);

