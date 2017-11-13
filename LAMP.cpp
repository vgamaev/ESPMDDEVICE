#include "LAMP.h"

bool lamp_on =  false;

// Включаем лампу
void turnOnLamp(int pinlamp) {
  digitalWrite(pinlamp, HIGH);
  Serial.print(pinlamp);
  Serial.println(" PIN ON");
//  sendServer(true);                /// Возможно лишнее
  lamp_on = true;
}
 
// Выключаем лампу
void turnOffLamp(int pinlamp) {
  digitalWrite(pinlamp, LOW);
  Serial.print(pinlamp);
  Serial.println(" PIN OFF");
  //sendServer(false);
  lamp_on = false;
}

// Изменяем состояние лампы
void toggleLamp(int pinlamp) {
  if (lamp_on == true) {
    turnOffLamp(pinlamp);
   } else {
    turnOnLamp(pinlamp);
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
  turnOnLamp(lamp);
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
  turnOffLamp(lamp);
  String message = "success";
  server.send(200, "text/plain", message);
}

// Получаем от сервера команды управления реле
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
    
  }else if(buf == "2")
  {
    
  }else if(buf == "3")
  {
    
  }

  if(pinN!=100)
  {
    buf = server.arg("state");
    Serial.println(buf);
    
    if (buf == "on")turnOnLamp(pinN);
    else if(buf == "off")turnOnLamp(pinN);
  }
  
  //turnOffLamp(lamp);
  String message = "success";
  server.send(200, "text/plain", message);
}

// Отправляем серверу MojorDomo события вкл./выкл.
void sendServer(bool state) {
  String post = "http://"+Config.serverIP+"/objects/?object="+Config.name+"&op=set&p="+Config.property+"&v=";
  post += (state ? "1" : "0");
  Serial.println(post);
  http.begin(post);
  int httpCode = http.GET(); 
  http.end();
}
