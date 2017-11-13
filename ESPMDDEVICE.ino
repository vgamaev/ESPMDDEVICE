
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
#include "ADC.h"

#ifdef IR_RESIVER
//=== IR Resiver ==============================
  int RECV_PIN = 5; //an IR detector/demodulatord is connected to GPIO pin 2
  int SEND_PIN = 15; //an IR led is connected to GPIO pin 0
#endif

//==== WIFI SWITCH =============================
//int lamp = 14; // Управляем реле через GPIO2
int button = 12; // "Ловим" выключатель через GPIO0

int RelayPin[MAX_RELAY];

//==============================================

int adcValue = 0;
int adcValueOld = 0;

//extern "C" { // эта часть обязательна чтобы получить доступ к функции initVariant
//#include "user_interface.h"
//}

const char* serverIndex = "<form method='POST' action='/update' enctype='multipart/form-data'><input type='file' name='update'><input type='submit' value='Update'></form>";


bool can_toggle = false;
int button_state;

ESP8266WebServer server (80) ; // веб сервер
HTTPClient http; // веб клиент

//===========================================================================================

void setup(void) {

  RelayInit();
  pinMode(button, INPUT_PULLUP); 
    
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

  adcRead();  // читаем вход ацп
  #ifdef IR_RESIVER 
    IRResiver();
  #endif
    // Проверяем нажатие выключателя
  button_state = digitalRead(button);
  if (button_state == HIGH && can_toggle) {
    toggleLamp(RELAY_1);
    can_toggle = false;
    delay(500);
  } else if (button_state == LOW) {
    can_toggle = true;
  }
}

