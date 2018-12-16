#include "KARNIZ.h"

#ifdef KARNIZ

//Обрабатываем ВЕБ запросы
void handleKarniz()
{
    String buf = server.arg("token");
    Serial.println(buf);
  
    if (Config.www_password != buf) {
      String message = "access denied";
      server.send(401, "text/plain", message);
      return;
    }
    buf = server.arg("command");
    char b[3];
    //int z = 100;
    if(buf.length())
    {
      buf.getBytes((unsigned char *)b, 3);
      KarnizMotorCommand = (int)StrToULong(b);
      Serial.print("WEB KarnizMotorCommand ");
      Serial.println(KarnizMotorCommand);
    }

    buf = server.arg("delay");
    if(buf.length())
    {
      buf.getBytes((unsigned char *)b, 3);
      KarnizMotorDelay = (int)StrToULong(b);
      Serial.print("WEB KarnizMotorDelay ");
      Serial.println(KarnizMotorDelay);
    }
    
     String message = "success";
    server.send(200, "text/plain", message);  
}

void InitKarniz() {
  // set all the motor control pins to outputs
  //pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  Serial.println("Init karniz...");
}

void MotorForward()
{
  if(KarnizMotorState != 1)
  {
    //digitalWrite(ENA, HIGH); // set speed to 200 out of possible range 0~255
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW); 
    KarnizMotorStartMillis = millis();
    Serial.println("Motor forward...");
    KarnizMotorState = 1;
  }
}

void MotorBackward()
{
  if(KarnizMotorState != 2)
  {
    //digitalWrite(ENA, HIGH); // set speed to 200 out of possible range 0~255
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    KarnizMotorStartMillis = millis();
    Serial.println("Motor backward...");
    KarnizMotorState = 2;
  }
}

void MotorStop()
{
  if(KarnizMotorState > 0)
  {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    Serial.println("Motor stop...");
    KarnizMotorState = 0;
    KarnizMotorCommand =0;
  }
}

void KarnizWork()
{
  if(KarnizMotorCommand > 0)
  {
    /*Serial.println("Karnix work ");
    Serial.print("KarnizMotorCommand ");
    Serial.println(KarnizMotorCommand);
    Serial.print("KarnizMotorDelay ");
    Serial.println(KarnizMotorDelay);
    Serial.println(); */
    int mtdelay = KarnizMotorDelay * 1000;
    Serial.print("mtdelay ");
    Serial.println(mtdelay);

    if(KarnizMotorCommand == 1) MotorForward();
    else if(KarnizMotorCommand == 2) MotorBackward();

    long currentMillis = millis();
    /*
    Serial.print("currentMillis ");
    Serial.println(currentMillis);
    Serial.print("KarnizMotorStartMillis ");
    Serial.println(KarnizMotorStartMillis);
    Serial.println(); */
    
    if(currentMillis - KarnizMotorStartMillis > mtdelay) MotorStop(); //останавливаем мотор если прошло больше заданого времени
  } else MotorStop();
}

void KarnizCommand(int Command, int MotorDelay)
{
  KarnizMotorCommand = Command;
  KarnizMotorDelay = MotorDelay;
}

#endif
