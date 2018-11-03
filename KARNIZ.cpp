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
    int z = 100;
    if(buf.length())
    {
      buf.getBytes((unsigned char *)b, 3);
      KarnizMotorCommand = (int)StrToULong(b);
    }

    buf = server.arg("delay");
    if(buf.length())
    {
      buf.getBytes((unsigned char *)b, 3);
      KarnizMotorCommand = (int)StrToULong(b);
    }
    
     String message = "success";
    server.send(200, "text/plain", message);  
}

void InitKarniz() {
  // set all the motor control pins to outputs
  //pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
}

void MotorForward()
{
  if(KarnizMotorState != 1)
  {
    //digitalWrite(ENA, HIGH); // set speed to 200 out of possible range 0~255
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW); 
    KarnizMotorState = 1;
  }
}

void MotorBackward()
{
  if(KarnizMotorState != 2)
  {
    //digitalWrite(ENA, HIGH); // set speed to 200 out of possible range 0~255
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    KarnizMotorState = 2;
  }
}

void MotorStop()
{
  if(KarnizMotorState > 0)
  {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    KarnizMotorState = 0;
    KarnizMotorCommand =0;
  }
}

void KarnizWork()
{
  if(KarnizMotorCommand > 0)
  {
    static long previousMillis = 0;                             
    long currentMillis = millis();
         
    if(currentMillis - previousMillis > KarnizMotorDelay) 
    {
        previousMillis = currentMillis;   
        if(KarnizMotorCommand == 1) MotorForward();
        else if(KarnizMotorCommand == 2) MotorBackward();
    }else MotorStop();
  } MotorStop();
}

void KarnizCommand(int Command, int MotorDelay)
{
  KarnizMotorCommand = Command;
  KarnizMotorDelay = MotorDelay;
}

#endif
