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
    const char *ssid1 = "Sonoff_T31";
    //String ssid = "ESPDEV_" + random(1000, 1000000);
    const char *password1 = "12345678";
    WiFi.mode(WIFI_AP_STA);
    //WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP(ssid1, password1);
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

 /* // Ждем пока подключимся к WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }  
  // Записываем текущий IP адресс
  if(Config.dhcp == "on")
    IPAddressToString(WiFi.localIP(),Config.ip);

  Serial.println(Config.ip);    */
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
        WIWI_Connect = 0;
      }
      previousMillis = currentMillis; 
   }
}
