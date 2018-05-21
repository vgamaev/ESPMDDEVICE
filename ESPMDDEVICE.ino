#include "ESPMDDEVICE.H"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
//#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266mDNS.h>

#include "ESPEEPROM.h"

#ifdef IR_RESIVER
  #include "ESPIR.h"
#endif

#include "ESPWIFI.h"
#include "ESPWEB.h"

#ifdef ADC
  #include "ADC.h"
#endif

#ifdef LED_MATRIX
  #include "LEDMATRIX.h"
#endif

#ifdef RF433MHZ
    #include "RF433MHZ.h"
unsigned long code433 =0;
#endif

#ifdef IR_RESIVER
//=== IR Resiver ==============================
  int RECV_PIN = 5; //an IR detector/demodulatord is connected to GPIO pin 2
  int SEND_PIN = 15; //an IR led is connected to GPIO pin 0
  unsigned long ResiverCode = 0;
  unsigned long TransmiterCode = 0;
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

//==============================================
#ifdef ADC
  int adcValue = 0;
  int adcValueOld = 0;
#endif

#ifdef LED_MATRIX
  int pinCS = 15;                           // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
  int numberOfHorizontalDisplays = 4;       // число матриц 8x8 MAX7219по горизонтали
  int numberOfVerticalDisplays = 1;         // Число матриц по вертикали
  String tapeMatrix;
  int wait = 80;                            // In milliseconds
  int spacer = 1;
  int width = 5 + spacer;                   // The font width is 5 pixels
  int MatrixOFF = 0 ;
  int MatrixCounter = 0;                    // Счетчик дляотображения бегущей строки
#endif

//=======================Светодиод WIFI=========================================
long WiFiCheckinterval = 1000; //Интервал проверки WiFi потключения
int WIWI_Connect=0;

//#ifdef WIFI_LED
  int WIFI_led = 13;             // Светодиод на выклчателе GPIO13
//#endif

//==============================================================================

const char* serverIndex = "<form method='POST' action='/update' enctype='multipart/form-data'><input type='file' name='update'><input type='submit' value='Update'></form>";

ESP8266WebServer server (80) ; // веб сервер
HTTPClient http; // веб клиент

String ssid1;
const char *password1 = "66666666";

unsigned long StrToULong(char *str)
{
 int len = strlen(str);
 unsigned long res = 0;
 unsigned long mul = 1;
 for(int i = len - 1; i >= 0; i--){
  res += mul * (unsigned long)(str[i] - '0');
  mul *= 10;
 }
 return res;
}

//===========================================================================================

void setup(void) {
  #ifdef RELAYS_ON
    RelayInit();
    ButtonInit();
    web_button_state_init();
  #endif
  #ifdef WIFI_LED
    pinMode(WIFI_led, OUTPUT);
    digitalWrite(WIFI_led, HIGH);           //Выключаем пин чтобы не мигала при старте
  #endif
    
  Serial.begin(9600);
  delay(10);

  //Записываем дефолтную конфигурацию
  DeraultConfig();
  
  // Читаем конфигурацию с EEPROM
  ConfigRead();
   
  // Включаем точку доступа инециализируем WIFI
  WiFi.hostname(Config.name);
  EnableAP();  
  ConectWIFI();

  Serial.println("Starting");
    
  // Назначем функции на запросы
  server.on("/setup", handleSetup);
  server.on("/", handleRoot);
  #ifdef RELAYS_ON
    server.on("/on", handleOn);
    server.on("/off", handleOff);
    server.on("/relay", handleRelay);
  #endif
  #ifdef IR_RESIVER 
    server.on("/ir",  handleIR);
    //Стартуем ИК приемопередатчик
    StartIR();
  #endif
  #ifdef LED_MATRIX 
    server.on("/informer",  handleLedMatrix);
    LedMatrixInit();
  #endif
  #ifdef RF433MHZ
    Start433();
  #endif
 // server.on("/firmware", FirmwarePage);
 // serveUupdate();                        //Update firmware
    //server.on("/off", HTTP_POST, handleOff);
  server.onNotFound(handleNotFound);
  
  // Стартуем WEB сервер
  server.begin();
}

void loop(void) {
  server.handleClient();
  WiFiLedStatus();
  #ifdef ADC
    adcRead();  // читаем вход ацп
  #endif
  
  #ifdef IR_RESIVER 
    IRResiver();
  #endif
  #ifdef RELAYS_ON
    ButtonSwitch();
  #endif
  #ifdef LED_MATRIX
    LedMatrix();
  #endif
  #ifdef RF433MHZ
    Resiver433();
  #endif
}

