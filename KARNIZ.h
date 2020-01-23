#ifndef KARNIZ_h
#define KARNIZ_h

#include "ESPMDDEVICE.H"

#ifdef KARNIZ
  #include <Arduino.h>
  #include <IRremoteESP8266.h>
  #include <ESP8266WebServer.h>
  #include <ESP8266HTTPClient.h>
  #include "ESPEEPROM.h"

  extern ESP8266WebServer server; // веб сервер
  extern HTTPClient http; // веб клиент

  unsigned long StrToULong(char *str);
  extern int ENA;
  extern int IN1;
  extern int IN2;

  extern int KarnizMotorState;
  extern int KarnizLength;
  extern int CurKarnizPosition;
  extern int KarnizPosition;
 
  void handleKarniz();
  void InitKarniz();
  void MotorForward();
  void MotorBackward(); 
  void MotorStop();
  void KarnizWork();
  void KarnizCommand(int Command, int MotorDelay);
  void SendCurKarnizPosition();
  void ReadCurPosMD();
  void OpenCloseKarniz();

  //обрабатываем нажатые кнопки
  void KarnizButtonSwitch(int nomer);

  void ReadEPROMKarnizLength();


#endif
#endif
