#include "ESPWEB.h"

bool web_button_state = false;

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


// функция для главной страници
void handleRoot() {

  if(WebAuth()== 0) return; // Проверяем логин и пароль
  
  String status = server.arg("status");
  if (web_button_state == false && status == "1")
  {
    turnOnLamp();
    web_button_state = true;
  } else if (web_button_state == true && status == "0")
  {
    turnOffLamp();
    web_button_state = false;
  }
  
  String temp = "<html>\
  <head>\
    <meta http-equiv='refresh' content='5'/>\
    <title>ESP8266 Demo</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
    <center><h1>Hello from ESP8266!</h1>\
    <h2><font color=red>LAMP Status: ";

  if (lamp_on == true) temp += "ON"; else temp += "OFF";

  temp += "</font></h2>\
    <form  method=get name=form>";
  if (lamp_on == true)
  {
    temp += "<button name=status value=0 type=submit style=height:80px;width:150px>LED Off</button>";
  } else
  {
    temp += "<button name=status value=1 type=submit style=height:80px;width:150px>LED On</button>";
  }
  temp += "</form><br />\
  </center>\
</html>" ;

  server.send ( 200, "text/html", temp );
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
      IPAddressToString(WiFi.softAPIP(),Config.ipap);
    }
    else Config.ap = "off";
    
    buf = server.arg("WWWAUTH");
    if (buf == "on") Config.wwwpass = "on";
    else Config.wwwpass = "off";
  
    Config.www_username = server.arg("WWWUSER");
    Config.www_password = server.arg("WWWPASS");
    
    Config.serverIP = server.arg("MDAdr");
    Config.name = server.arg("MDObj");
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
              <tr> <td>Adress      </td><td> <input type= text size=20 maxlength=20 name=MDAdr value="; temp += Config.serverIP; temp += ">  </td> </tr>\
              <tr> <td>Name object </td><td> <input type= text size=20 maxlength=20 name=MDObj value="; temp += Config.name; temp += ">      </td> </tr>\
              <tr> <td>Object      </td><td> <input type= text size=20 maxlength=20 name=MDStatus value="; temp += Config.property; temp += ">  </td> </tr>\
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

 /*           <tr> <td>MASK   </td><td> <input type= text size=15 maxlength=15 name=MASK value="; temp += Config.mask; if(Config.dhcp == "on") temp +=" disabled"; temp += ">  </td> </tr>\
            <tr> <td>Gateway </td><td> <input type=text size=15 maxlength=15 name=GW   value="; temp += Config.gw;  if(Config.dhcp == "on") temp +=" disabled"; temp += ">  </td> </tr>\
            <tr> <td>DNS    </td><td> <input type=text  size=15 maxlength=15 name=DNS  value="; temp += Config.dns;  if(Config.dhcp == "on") temp +=" disabled"; temp += ">  </td> </tr>\
 */



// функция для недействительных запросов
void handleNotFound() {
  Serial.println("not found 404");
  String message = "not found";
  server.send(404, "text/plain", message);
}


/*
// Устанавливаем MAC чтобы давать одинаковый IP
void initVariant() {
  uint8_t mac[6] = {0x00, 0xA3, 0xA0, 0x1C, 0x8C, 0x45};
  // wifi_set_macaddr(STATION_IF, &mac[0]);
}*/
