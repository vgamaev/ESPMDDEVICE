#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
//#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266mDNS.h>

#include "ESPEEPROM.h"
#include "ESPIR.h"
#include "LAMP.h"
#include "ESPWIFI.h"
#include "ESPWEB.h"

//=== IR Resiver ==============================
int RECV_PIN = 2; //an IR detector/demodulatord is connected to GPIO pin 2
int SEND_PIN = 15; //an IR led is connected to GPIO pin 0

//==== WIFI SWITCH =============================
int lamp = 14; // Управляем реле через GPIO2
int button = 18; // "Ловим" выключатель через GPIO0

//==============================================


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

  // Назначаем пины и их режимы.
 // pinMode(lamp, OUTPUT);
 // digitalWrite(lamp, LOW);           //Выключаем пин чтобы не мигала при старте
 // pinMode(button, INPUT_PULLUP); 
  //turnOffLamp()
  
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
  server.on("/ir",  handleIR);
 // server.on("/firmware", FirmwarePage);
 // serveUupdate();                        //Update firmware
    //server.on("/off", HTTP_POST, handleOff);
  server.onNotFound(handleNotFound);
  
  // Стартуем WEB сервер
  server.begin();
  
  //Стартуем ИК приемопередатчик
  StartIR();
  
  // посылаем начальный статус устройства
  //sendServer(false);
}

void loop(void) {
  server.handleClient();

  IRResiver();
  // Проверяем нажатие выключателя
  button_state = digitalRead(button);
  if (button_state == HIGH && can_toggle) {
    toggleLamp(lamp);
    can_toggle = false;
    delay(500);
  } else if (button_state == LOW) {
    can_toggle = true;
  }
}

