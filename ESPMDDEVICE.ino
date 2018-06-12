#include "MAINVARIABLE.h"

const char* serverIndex = "<form method='POST' action='/update' enctype='multipart/form-data'><input type='file' name='update'><input type='submit' value='Update'></form>";

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

  server.on("/test", HTTP_GET, [](){
      server.sendHeader("Connection", "close");
      server.send(200, "text/html", serverIndex);
    });
  server.on("/update", HTTP_POST, funk1,funk2);
 
  server.onNotFound(handleNotFound);
  
  // Стартуем WEB сервер
  server.begin();
}

void funk1()
{
   server.sendHeader("Connection", "close");
   server.send(200, "text/plain", (Update.hasError())?"FAIL":"OK");
   ESP.restart();
}

void funk2()
{
      HTTPUpload& upload = server.upload();
      if(upload.status == UPLOAD_FILE_START){
        Serial.setDebugOutput(true);
        WiFiUDP::stopAll();
        Serial.printf("Update: %s\n", upload.filename.c_str());
        uint32_t maxSketchSpace = (ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000;
        if(!Update.begin(maxSketchSpace)){//start with max available size
          Update.printError(Serial);
        }
      } else if(upload.status == UPLOAD_FILE_WRITE){
        if(Update.write(upload.buf, upload.currentSize) != upload.currentSize){
          Update.printError(Serial);
        }
      } else if(upload.status == UPLOAD_FILE_END){
        if(Update.end(true)){ //true to set the size to the current progress
          Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
        } else {
          Update.printError(Serial);
        }
        Serial.setDebugOutput(false);
      }
      yield();
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

