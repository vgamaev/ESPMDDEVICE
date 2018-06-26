#include "WEBUPDATE.h"

#ifdef WEBUPDATE

//Страница выбора файла прошивки
void handleWebUpdate()
{
  if(WebAuth()== 0) return; // Проверяем логин и пароль
  String serverIndex = "<html>\
                          <head>\
                            <style>\
                               body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
                            </style>\
                          </head>\
                          <form method='POST' action='/update' enctype='multipart/form-data'> \
                            <body>\
                              <center> \
                                <a href=.>Главная</a> <a href=setup>Настройка</a> <a href=webupdate>Обновления</a>\
                                <h1>Firmware update </h1>\
                                <input type='file' name='update'> \
                                <input type='submit' value='Update'> \ 
                              </center> \
                            </body>\
                          </form> \
                       </html>" ;
      
      server.sendHeader("Connection", "close");
      server.send(200, "text/html", serverIndex);
}

void handleUpdate1()
{
   server.sendHeader("Connection", "close");
   server.send(200, "text/plain", (Update.hasError())?"FAIL":"OK");
   ESP.restart();
}

void handleUpdate2()
{
      if(WebAuth()== 0) return; // Проверяем логин и пароль
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

#endif



