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

#include "LAMP.h"
#include "ESPWIFI.h"
#include "ESPWEB.h"

#ifdef ADC
  #include "ADC.h"
#endif

#ifdef IR_RESIVER
//=== IR Resiver ==============================
  int RECV_PIN = 5; //an IR detector/demodulatord is connected to GPIO pin 2
  int SEND_PIN = 15; //an IR led is connected to GPIO pin 0
#endif

//==== WIFI SWITCH =============================
//int lamp = 14; // Управляем реле через GPIO2
//int button = 12; // "Ловим" выключатель через GPIO0

int RelayPin[MAX_RELAY];
int lamp_on[MAX_RELAY];

int ButtonPin[MAX_BUTTON];
int can_toggle[MAX_BUTTON];
int button_state[MAX_BUTTON];
bool web_button_state[MAX_RELAY];

//==============================================
#ifdef ADC
  int adcValue = 0;
  int adcValueOld = 0;
#endif

//=======================Светодиод WIFI=========================================
long WiFiCheckinterval = 1000; //Интервал проверки WiFi потключения
int WIFI_led = 13;             // Светодиод на выклчателе GPIO13
int WIWI_Connect=0;
//==============================================================================

const char* serverIndex = "<form method='POST' action='/update' enctype='multipart/form-data'><input type='file' name='update'><input type='submit' value='Update'></form>";

ESP8266WebServer server (80) ; // веб сервер
HTTPClient http; // веб клиент

//===========================================================================================

void setup(void) {

  RelayInit();
  ButtonInit();
  pinMode(WIFI_led, OUTPUT);
  digitalWrite(WIFI_led, HIGH);           //Выключаем пин чтобы не мигала при старте
  web_button_state_init();
  
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
  server.on("/", handleRoot);
  server.on("/setup", handleSetup);
  server.on("/on", handleOn);
  server.on("/off", handleOff);
  server.on("/relay", handleRelay);
#ifdef IR_RESIVER 
  server.on("/ir",  handleIR);
#endif
 // server.on("/firmware", FirmwarePage);
 // serveUupdate();                        //Update firmware
    //server.on("/off", HTTP_POST, handleOff);
  server.onNotFound(handleNotFound);
  
  // Стартуем WEB сервер
  server.begin();

#ifdef IR_RESIVER 
  //Стартуем ИК приемопередатчик
  StartIR();
#endif  
  // посылаем начальный статус устройства
  //sendServer(false);
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
  ButtonSwitch();
}

