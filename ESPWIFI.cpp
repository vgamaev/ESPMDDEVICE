#include "ESPWIFI.h"

// Функция конвертирует IP адрес в строку
void IPAddressToString(IPAddress ip, String &StrIP)
{
   StrIP = String(ip[0])+"."; 
   StrIP += String(ip[1])+"."; 
   StrIP += String(ip[2])+"."; 
   StrIP += String(ip[3]); 
   Serial.print("Convert "); 
   Serial.println(StrIP); 
} 

void EnableAP(){
  if(Config.ap == "on"){
    //const char *ssid2 = "Sonoff_T1";
    int rand = random(100, 10000);
    ssid1 = "ESPDEV_" + (String)rand;
    
    //конвентируем String в строку символов 
    char ssid2[ssid1.length()+1];
    ssid1.toCharArray(ssid2, ssid1.length()+1);
    WiFi.mode(WIFI_AP_STA);
    //WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP(ssid2, password1);
    IPAddressToString(WiFi.softAPIP(),Config.ipap);
    Serial.println("Accss point ON");
  } else WiFi.mode(WIFI_STA);
}

void ConectWIFI()
{
 //конвентируем String в строку символов 
  char ssid[Config.ssid.length()+1];
  Config.ssid.toCharArray(ssid,Config.ssid.length()+1);
  
  char password[Config.password.length()+1];
  Config.password.toCharArray(password,Config.password.length()+1);
 
 // Потключаемся к  WIFI
  WiFi.begin(ssid, password);
}

//Индикация потключения по wifi
void WiFiLedStatus()
{
  static long previousMillis = 0;                             
  long currentMillis = millis();
  
  if(currentMillis - previousMillis > WiFiCheckinterval) 
   {   
      if(WiFi.status() == WL_CONNECTED && WIWI_Connect == 0) 
      {  
        #ifdef WIFI_LED
          digitalWrite(WIFI_led, LOW);
        #endif
        if(Config.dhcp == "on")    IPAddressToString(WiFi.localIP(),Config.ip);
        Serial.println(Config.ip);
        WIWI_Connect = 1;
      }
      else if(WiFi.status() != WL_CONNECTED)
      {
        #ifdef WIFI_LED
          digitalWrite(WIFI_led, HIGH);
        #endif
        #ifdef LED_MATRIX
          tapeMatrix = "Нет подключения по WIFI";
          MatrixCounter = 0;
        #endif
        WIWI_Connect = 0;
      }
      previousMillis = currentMillis; 
   }
}
