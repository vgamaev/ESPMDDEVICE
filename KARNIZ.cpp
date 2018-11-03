#include "KARNIZ.h"

#ifdef KARNIZ
#include <Arduino.h>

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
    KarnizMotorState = 2;
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
  }
}

void KarnizWork()
{
  if(KarnizMotorCommand > 0)
  {
    static long previousMillis = 0;                             
    long currentMillis = millis();
         
    if(currentMillis - previousMillis > 1000) 
    {
        previousMillis = currentMillis;    
    }else MotorStop();
  } MotorStop();
}

#endif
