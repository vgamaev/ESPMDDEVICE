#include "MAINVARIABLE.h"

//==============================================================================
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
  #ifdef DHT22
    dhtInit();
  #endif
  
  #ifdef KARNIZ
    server.on("/karniz",  handleKarniz);
    InitKarniz();
  #endif

  #ifdef WEBUPDATE
    server.on("/webupdate", HTTP_GET, handleWebUpdate);
    server.on("/update", HTTP_POST, handleUpdate1, handleUpdate2);
  #endif
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
  #ifdef DHT22
    dhtRead();
  #endif
  #ifdef KARNIZ
    KarnizWork();
  #endif
}
