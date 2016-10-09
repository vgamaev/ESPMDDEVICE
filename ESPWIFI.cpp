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
    const char *ssid1 = "MY_ESP";
    const char *password1 = "8849";
    //WiFi.mode(WIFI_AP);
    //WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP(ssid1, password1);
    IPAddressToString(WiFi.softAPIP(),Config.ipap);
    //Serial.println("Accss point ON");
  }
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

  // Ждем пока подключимся к WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  // Записываем текущий IP адресс
  if(Config.dhcp == "on")
    IPAddressToString(WiFi.localIP(),Config.ip);

  Serial.println(Config.ip);
}
