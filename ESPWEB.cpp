#include "ESPWEB.h"

//===================================== WEB Auth=================================================================
bool WebAuth() {

  if(Config.wwwpass == "on")
  {
      char www_username[Config.www_username.length()+1];
      Config.www_username.toCharArray(www_username,Config.www_username.length()+1);
      char www_password[Config.www_password.length()+1];
      Config.www_password.toCharArray(www_password,Config.www_password.length()+1);
      
      if(!server.authenticate(www_username, www_password))
          {
            server.requestAuthentication();
            return 0;
          }
  } else return 1;
}


// Находим все точки доступа и записываем их названия в буфер вэб страници
void WIFIScan(String & temp)
{
  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  if (n == 0)
   temp+="no networks found";
  else
  {
    temp += "</br>";
    temp += n;
    temp += " networks found";
    temp += "</br></br>";
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      temp += i + 1;
      temp += ": ";
      temp += WiFi.SSID(i);
      temp += " RSSI ";
      temp += WiFi.RSSI(i);
      temp += "</br>";
     // Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*");
      delay(10);
    }
  }
  //Serial.println("");
} 


// Раббираем ответ от ВЭБ страници конфигурвции.
void WebParser(){

  String buf = server.arg("save");
  
  if (buf == "save"){
    Config.ssid = server.arg("SSID");
    Config.password = server.arg("PASS");
    
    buf = server.arg("SETUPAP");
    if (buf == "on") 
    {
      Config.ap = "on";
      EnableAP();
    }
    else 
    {
      Config.ap = "off";
      EnableAP();
    }
    
    buf = server.arg("WWWAUTH");
    if (buf == "on") Config.wwwpass = "on";
    else Config.wwwpass = "off";
  
    Config.www_username = server.arg("WWWUSER");
    Config.www_password = server.arg("WWWPASS");
    
    Config.serverIP = server.arg("MDAdr");
    Config.name = server.arg("MDObj");
    #if defined (Sonof_T1_2_button) || defined (Sonof_T1_3_button)
    Config.name2 = server.arg("MDObj2");
    #endif
    #ifdef Sonof_T1_3_button
    Config.name3 = server.arg("MDObj3");
    #endif
    Config.property = server.arg("MDStatus");

    buf = server.arg("DHCP");
    if (buf == "on") {
       Config.dhcp = "on";
       IPAddressToString(WiFi.localIP(),Config.ip);
    }
    
    else {
      Config.dhcp = "off";
      Config.ip = server.arg("IP");
      Config.mask = server.arg("MASK");
      Config.gw = server.arg("GW");
      Config.dns = server.arg("DNS");
    }
    
    ConfigSave();
    Serial.println("save conf");
  }
}

//Обработка страници с информера
void WebParseButton()
{
    #ifdef RELAYS_ON
      String status = server.arg("RELAY1");
      Serial.print("status1 ");
      Serial.println(status);
      WebButtonRead(status, RELAY_1);
    
      #if defined (Sonof_T1_2_button) || defined (Sonof_T1_3_button)
          status = server.arg("RELAY2");
          Serial.print("status2 ");
          Serial.println(status);
          WebButtonRead(status, RELAY_2);
      #endif
       
      #ifdef Sonof_T1_3_button
          status = server.arg("RELAY3");
          Serial.print("status3 ");
          Serial.println(status);
          WebButtonRead(status, RELAY_3);
      #endif
    #endif
}

//Обработка страници с информера
void WebParserinformer()
{
  String buf = server.arg("send");
  if (buf == "send")
  {
    tapeMatrix = server.arg("infsrt");
    MatrixCounter = 0;      //Начинаем новую строку сначала
  }
}

//Обработка страници с ИК
void WebParserIR()
{ 
  #ifdef IR_RESIVER
    String buf = server.arg("send");
    if (buf == "send")
    {
      buf = server.arg("ircode");
      Serial.println(buf);
      char b[32];
      //long a = StrToULong(b);  //Проверить
      buf.getBytes((unsigned char *)b, 32);
      Serial.println(StrToULong(b));
      IRTransmiter(StrToULong(b));
      TransmiterCode = StrToULong(b);
    }
  #endif
}

//=======================================SETUP======================================================

// функция для страници настройки устройства
void handleSetup() {

  if(WebAuth()== 0) return; //Проверяем логин и пароль на страницу
  WebParser();               // Разбирае ответ от вэб страници
  
  String temp = "<html>\
    <head>\
       <style>\
        body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
      </style>\
    </head>\
    <form method=get>\
      <body>\
        <center> \
        <a href=.>Главная</a> <a href=setup>Настройка</a> <a href=webupdate>Обновления</a>\
        <h1>Setup devise </h1>\
           <table border=\"1\">\
           <tr>\
           <td valign=\"top\" width=\"280\"> \
           <table>\
               <tr> <td> WIFI: </td> </tr>\
               <tr> <td>SSID:</td>       <td> <input type=text size=12 maxlength=12 name=SSID value="; temp += Config.ssid; temp += ">          </td> </tr>\
               <tr> <td>WiFi pass:       </td><td> <input type=text size=12 maxlength=12 name=PASS value="; temp += Config.password; temp += ">      </td> </tr>\
               <tr> <td>Enable setup AP: </td><td> <input type=checkbox name= SETUPAP id="; temp += Config.ap; if(Config.ap == "on") temp +=" checked=checked" ;  temp += "> </td> </tr>\
               <td>IP  AP:               </td><td> <input type= text size=15 maxlength=15 disabled name=IPAP   value="; temp += Config.ipap; temp += ">  </td> </tr>\
           </table>";
           WIFIScan(temp);
           temp += "</td>\     
           <td valign=\"top\">\
           <table>\
               <tr> <td>Secure:</td> </tr>\
               <tr> <td>Use auth: </td><td> <input type=checkbox name= WWWAUTH id="; temp += Config.wwwpass; if(Config.wwwpass == "on") temp +=" checked=checked" ;  temp += "> </td> </tr>\
               <tr> <td>Login:    </td><td> <input type=text size=12 maxlength=12 name=WWWUSER value="; temp += Config.www_username; temp += ">   </td> </tr>\
               <tr> <td>Password: </td><td> <input type=text size=12 maxlength=12 name=WWWPASS value="; temp += Config.www_password; temp += ">   </td> </tr>\
           </table> \
           </br> \
           <table>\
           <tr><td> Mojordomo: </td> </tr>\
              <tr> <td>Adress      </td><td> <input type= text size=20 maxlength=20 name=MDAdr value="; temp += Config.serverIP; temp += ">  </td> </tr>";
                temp += "<tr> <td>Name object  </td><td> <input type= text size=20 maxlength=20 name=MDObj value="; temp += Config.name; temp += ">      </td> </tr>";
              #if defined (Sonof_T1_2_button) || defined (Sonof_T1_3_button)
                temp += "<tr> <td>Name object 2 </td><td> <input type= text size=20 maxlength=20 name=MDObj2 value="; temp += Config.name2; temp += ">      </td> </tr>";
              #endif
              #ifdef Sonof_T1_3_button
                temp += "<tr> <td>Name object 3 </td><td> <input type= text size=20 maxlength=20 name=MDObj3 value="; temp += Config.name3; temp += ">      </td> </tr>";
              #endif
              temp += "<tr> <td>Property  </td><td> <input type= text size=20 maxlength=20 name=MDStatus value="; temp += Config.property; temp += ">  </td> </tr>\
          </table>\
          </br> \
          <table>\
            <tr> <td> Conect sitting:  </td> </tr>\
            <tr> <td>DHCP:  </td><td> <input type= checkbox name= DHCP id="; temp += Config.dhcp; if(Config.dhcp == "on") temp +=" checked=checked" ;  temp += ">  </td> </tr>\
            <tr> <td>IP     </td><td> <input type= text size=15 maxlength=15 name=IP   value="; temp += Config.ip;   if(Config.dhcp == "on") temp +=" disabled"; temp += ">  </td> </tr>\
            </table>\
          </td>\
          </tr>\
          </table>\
          </br>\
               \
          <input type= submit name=save value= save ><br/>\
     </form>\
     </center> \
  </body>\
  </html>\
  </html>" ;

  server.send ( 200, "text/html", temp );
}

 //===============================================================================================
// функция для главной страници
void handleRoot() {
  String status;
  if(WebAuth()== 0) return; // Проверяем логин и пароль

  #ifdef RELAYS_ON
    WebParseButton();
  #endif
  #ifdef LED_MATRIX
    WebParserinformer();
  #endif
  #ifdef IR_RESIVER
    WebParserIR();
  #endif
  
  String temp = "<html>\
  <head>\
    <meta http-equiv='refresh' content=";
    #ifdef RELAYS_ON
      temp += "'5'"; //добавляем автообновление страници
    #endif
    #if defined (LED_MATRIX) || defined (IR_RESIVER) || defined (RF433MHZ) //#ifdef LED_MATRIX
      temp += "'180'"; //добавляем автообновление страници
    #endif
    temp += " charset='utf-8'/>\
    <title>ESPDEVICE</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body><center>\
  <a href=.>Главная</a> <a href=setup>Настройка</a> <a href=webupdate>Обновления</a>";

// Relay Botton Pages  
  #ifdef RELAYS_ON  
    temp += "<h1>WIFI Switch</h1>\
             <h3><font color=red>LAMP Status: ";

    if (lamp_on[RELAY_1] == true) temp += " LAMP1 ON | "; else temp += " LAMP1 OFF | ";
    
    #if defined (Sonof_T1_2_button) || defined (Sonof_T1_3_button)
        if (lamp_on[RELAY_2] == true) temp += " LAMP2 ON | "; else temp += " LAMP2 OFF | ";
    #endif
    #ifdef Sonof_T1_3_button
        if (lamp_on[RELAY_3] == true) temp += " LAMP3 ON | "; else temp += " LAMP3 OFF | ";
    #endif
    
    temp += "</font></h3>\
      <form  method=get name=form>";
    if (web_button_state[RELAY_1] == true)
    {
      temp += "<button name=RELAY1 value=0 type=submit style=height:80px;width:150px>LAMP1 On//Off</button>";
    } else
    {
      temp += "<button name=RELAY1 value=1 type=submit style=height:80px;width:150px>LAMP1 On/Off</button>";
    }
      
    #if defined (Sonof_T1_2_button) || defined (Sonof_T1_3_button)
        if (web_button_state[RELAY_2] == true)
        {
          temp += "<button name=RELAY2 value=0 type=submit style=height:80px;width:150px>LAMP2 On/Off</button>";
        } else
        {
          temp += "<button name=RELAY2 value=1 type=submit style=height:80px;width:150px>LAMP2 On/OFF</button>";
        } 
    #endif
     
    #ifdef Sonof_T1_3_button
        if (web_button_state[RELAY_3] == true)
        {
          temp += "<button name=RELAY3 value=0 type=submit style=height:80px;width:150px>LAMP3 On/Off</button>";
        } else
        {
          temp += "<button name=RELAY3 value=1 type=submit style=height:80px;width:150px>LAMP3 On/off</button>";
        }  
    #endif
    temp += "</form><br />";
  #endif

//Informer peges
  #ifdef LED_MATRIX  
    temp += "<h1>LED MATRIX INFORMER</h1>\
             <h3><font color=red>Строка на информере: ";
    temp += tapeMatrix;
    temp += "</font></h3> \
             <form  method=get name=form>";
    temp += "Ввидите текст для отправки :<input type=text size=30 maxlength=100 name=infsrt value=\"\"> \
             <input type= submit name=send value=send ><br/> \
             </form><br />";
  #endif 

  //IR peges
  #ifdef IR_RESIVER  
    temp += "<h1>IR RESIVER-TRANSMITER</h1>\
             <h3><font color=red>Принятый код по ИК: ";
    temp += ResiverCode;
    temp += "</font></h3>";
    
    temp += "<h3><font color=red>Отправленный код по ИК: ";
    temp += TransmiterCode;
    temp += "</font></h3> \
             <form  method=get name=form>";
    temp += "Ввидите код для отправки :<input type=text size=10 maxlength=10 name=ircode value=\"\"> \
             <input type= submit name=send value=send ><br/> \
             </form><br />";
  #endif 

  //ADC peges
  #ifdef ADC  
    temp += "<h3><font color=red>Освещеность: ";
    temp += adcValue;
    temp += "</font></h3>";
  #endif 

  //433MHZ peges
  #ifdef RF433MHZ  
    temp += "<h1>433МГц приемник</h1>\
             <h3><font color=red>Принятый код по 433МГЦ: ";
    temp += code433;
    temp += "</font></h3>";
  #endif 

  //DHT22 peges
  #ifdef DHT22  
    temp += "<h1>Метеостанция</h1>\
             <h3><font color=red>Температура: ";
    temp += tempDHT;
    temp += " С</font></h3>\
             <h3><font color=red>Влажность: ";
    temp += humDHT;
    temp += "% </font></h3>\
             <h3><font color=red>Ощущаеиая температура: ";
    temp += hicDHT;
    temp += "С </font></h3>";
  #endif 

  temp += "<body></center></html>" ;
  server.send ( 200, "text/html", temp );
}


// функция для недействительных запросов
void handleNotFound() {
  Serial.println("not found 404");
  String message = "Not found";
  server.send(404, "text/plain", message);
}


/*
// Устанавливаем MAC чтобы давать одинаковый IP
void initVariant() {
  uint8_t mac[6] = {0x00, 0xA3, 0xA0, 0x1C, 0x8C, 0x45};
  // wifi_set_macaddr(STATION_IF, &mac[0]);
}*/

/*
 //=================================UPDATE FIRMWARE =====================================
void serveUupdate()
{
  server.on("/update", HTTP_POST, [](){
        server.sendHeader("Connection", "close");
        server.sendHeader("Access-Control-Allow-Origin", "*");
        server.send(200, "text/plain", (Update.hasError())?"FAIL":"OK");
        ESP.restart();
      },[](){
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
      });
}

void FirmwarePage()
{
      server.sendHeader("Connection", "close");
      server.sendHeader("Access-Control-Allow-Origin", "*");
      server.send(200, "text/html", serverIndex);
}*/



