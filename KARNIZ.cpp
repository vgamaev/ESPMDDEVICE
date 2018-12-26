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
    buf = server.arg("position");
    char b[3];
    if(buf.length())
    {
      buf.getBytes((unsigned char *)b, 3);
      KarnizPosition = (int)StrToULong(b);
      Serial.print("WEB KarnizPosition ");
      Serial.println(KarnizPosition);
    }

    buf = server.arg("calibrate");
    if(buf.length())
    {
      buf.getBytes((unsigned char *)b, 3);
      CurKarnizPosition = (int)StrToULong(b);
      KarnizPosition = CurKarnizPosition;
      Serial.print("Calibrate CurKarnizPosition ");
      Serial.println(CurKarnizPosition);
      
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
  //SendCurKarnizPosition();
  Serial.println();
  Serial.println("Init karniz...");
  ReadCurPosMD();
}

void MotorForward()
{
  if(KarnizMotorState != 1)
  {
    //digitalWrite(ENA, HIGH); // set speed to 200 out of possible range 0~255
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW); 
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
    SendCurKarnizPosition();
    Serial.println("Motor stop...");
    KarnizMotorState = 0;
  }
}

void KarnizWork()
{
    static long previousMillis = 0;
    long KarnizCurrentMillis = millis();
    static long motorDelay = 1;

    if(KarnizCurrentMillis - previousMillis > 1000) 
    {
      previousMillis = KarnizCurrentMillis;
      Serial.print("KarnizPosition ");
      Serial.println(KarnizPosition);
      Serial.print("CurKarnizPosition ");
      Serial.println(CurKarnizPosition);
      
      if(KarnizPosition == CurKarnizPosition || KarnizPosition > KarnizLength) 
      {
        MotorStop(); //останавливаем мотор
        motorDelay = 1;
      }
      else if(KarnizPosition > CurKarnizPosition)
           {
              if(motorDelay < 2) {    // нужно подождать пока мотор остановится при резкой смене напрвления
                MotorStop()
                motorDelay ++ ;
              }
              else {
                MotorForward();
                CurKarnizPosition ++ ;
              }
           }
          else if(KarnizPosition < CurKarnizPosition)
          {
             if(motorDelay > 0) {     // нужно подождать пока мотор остановится при резкой смене напрвления
                MotorStop()
                motorDelay -- ;
              }
             else {
                MotorBackward();
                CurKarnizPosition -- ;
             }
         }
    }       
}

void SendCurKarnizPosition()
{
  String post = "http://"+Config.serverIP+"/objects/?object="+Config.name+"&op=set&p=slider2&v="+CurKarnizPosition;
        Serial.println(post);
        http.begin(post);
        int httpCode = http.GET(); 
        http.end();
}

void ReadCurPosMD()
{
  String post = "http://"+Config.serverIP+"/objects/?op=m&object="+Config.name+"&m=StartPos";  
        Serial.println(post);
        http.begin(post);
        int httpCode = http.GET(); 
        http.end();
}
/*
void KarnizCommand(int Command, int MotorDelay)
{
  KarnizMotorCommand = Command;
  KarnizMotorDelay = MotorDelay;
} */

#endif
