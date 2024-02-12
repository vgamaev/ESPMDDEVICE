#include "LAMP.h"

#ifdef RELAYS_ON

// Инециализируем выходы для реле
void RelayInit()
{
   RelayPin[0]=12;
   
   #if defined (Sonof_T1_2_button) || defined (Sonof_T1_3_button)
      RelayPin[1]=5;
   #endif
   
   #ifdef Sonof_T1_3_button
      RelayPin[2]=4;
   #endif
   
  // Назначаем пины и их режимы.
   for(int i=0; i<MAX_RELAY; i++ ) 
   {
      pinMode(RelayPin[i], OUTPUT);
      turnOffLamp(i);
   }
   
   VersionCode += VersionRelay ;
}

// Инециализируем входы для кнопок
void ButtonInit()
{
   ButtonPin[0]=0;  //def 0 15 16 13 6 7 4 3 2 1
   
   #if defined (Sonof_T1_2_button) || defined (Sonof_T1_3_button)
      ButtonPin[1]=9;
   #endif
   
   #ifdef Sonof_T1_3_button
      ButtonPin[2]=10;
   #endif
   
  // Назначаем пины и их режимы.
   for(int i=0; i<MAX_BUTTON; i++ ) 
   {
      pinMode(ButtonPin[i], INPUT_PULLUP);
      can_toggle[i]=0;
      button_state[i]=0;
   }
}


// Проверяем нажатие кнопок выключателя
void ButtonRead()
{
  for(int i=0; i<MAX_BUTTON; i++) button_state[i] = digitalRead(ButtonPin[i]);
}

// Обрабатываем нажатие кнопок
void ButtonSwitch()
{
  // Проверяем нажатие кнопок выключателя
  ButtonRead();
  for(int i=0; i<MAX_BUTTON; i++)
  {
    if(button_state[i] == HIGH && can_toggle[i]) {
      toggleLamp(i);
      sendServer(lamp_on[i], i);
      can_toggle[i] = false;
      delay(500);
    }else if (button_state[i] == LOW) {
      can_toggle[i] = true;
    }
  }
}

// Включаем лампу
void turnOnLamp(int nomer) 
{
  digitalWrite(RelayPin[nomer], HIGH);
  Serial.print(RelayPin[nomer]);
  Serial.println(" PIN ON");
//  sendServer(true);                /// Возможно лишнее
  lamp_on[nomer] = true;
}
 
// Выключаем лампу
void turnOffLamp(int nomer) 
{
  digitalWrite(RelayPin[nomer], LOW);
  Serial.print(RelayPin[nomer]);
  Serial.println(" PIN OFF");
  //sendServer(false);
  lamp_on[nomer] = false;
}

// Изменяем состояние лампы
void toggleLamp(int nomer) {
  if (lamp_on[nomer] == true) {
    turnOffLamp(nomer);
   } else {
    turnOnLamp(nomer);
   }
}

// Получаем от сервера команду включить
void handleOn() {
  String token = server.arg("token");
  Serial.println(token);
  // Serial.println("poken");

  if (Config.www_password != token) {
    String message = "access denied";
    server.send(401, "text/plain", message);
    return;
  }
  turnOnLamp(RELAY_1);
  String message = "success";
  server.send(200, "text/plain", message);
}

// Получаем от сервера команду выключить
void handleOff() {
  String token = server.arg("token");
  Serial.println(token);
  if (Config.www_password != token) {
    String message = "access denied";
    server.send(401, "text/plain", message);
    return;
  }
  turnOffLamp(RELAY_1);
  String message = "success";
  server.send(200, "text/plain", message);
}

// Получаем от сервера команды управления реле
//пример запроса http://192.168.1.119/relay?token=esp8266&relay=3&state=off
void handleRelay()
{
  int pinN=100;
  String buf = server.arg("token");
  Serial.println(buf);
  if (Config.www_password != buf) {
    String message = "access denied";
    server.send(401, "text/plain", message);
    return;
  }
  buf = server.arg("relay");
  Serial.println(buf);

  if (buf == "1")
  {
    pinN=RELAY_1; 
  }
  #if defined (Sonof_T1_2_button) || defined (Sonof_T1_3_button)
  else if(buf == "2")
  {
    pinN=RELAY_2;
  }
  #endif
  #ifdef Sonof_T1_3_button
  else if(buf == "3")
  {
    pinN=RELAY_3; 
  }
  #endif
  
  if(pinN!=100)
  {
    buf = server.arg("state");
    Serial.println(buf);
    
    if (buf == "on")turnOnLamp(pinN);
    else if(buf == "off")turnOffLamp(pinN);
  }
  String message = "success";
  server.send(200, "text/plain", message);
}

void WebButtonRead(String status, int RelayN)
{
  //Serial.print("status ");
  //Serial.println(status);
  //Serial.print("RelayN ");
  //Serial.println(RelayN);
  if (web_button_state[RelayN] == false && status == "1")
    {
      turnOnLamp(RelayN);
      sendServer(true, RelayN);
      web_button_state[RelayN] = true;
    } else if (web_button_state[RelayN] == true && status == "0") //&& lamp_on[RelayN] == true
    {
      turnOffLamp(RelayN);
      sendServer(false, RelayN);
      web_button_state[RelayN] = false;
    }
}

//===================================== Init button state ========================================================
void web_button_state_init()
{
  for(int i=0; i<MAX_RELAY; i++ ) web_button_state[i]= false;
}

// Отправляем серверу MojorDomo события вкл./выкл.
void sendServer(bool state, int relay_n) 
{
  String ObjectsName;
  switch (relay_n)
  {
    case RELAY_1:
      ObjectsName = Config.name;
    break;
    #if defined (Sonof_T1_2_button) || defined (Sonof_T1_3_button)
    case RELAY_2:
      ObjectsName = Config.name2;
    break;
    #endif
    #ifdef Sonof_T1_3_button
    case RELAY_3:
      ObjectsName = Config.name3;
    break;
    #endif
  }
  String post = "http://"+Config.serverIP+"/objects/?object="+ObjectsName+"&op=set&p="+Config.property+"&v=";
  post += (state ? "1" : "0");
  Serial.println(post);
  http.begin(client, post);
  int httpCode = http.GET(); 
  http.end();
}

#endif
