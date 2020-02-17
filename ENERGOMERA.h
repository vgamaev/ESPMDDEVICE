#ifndef ENERGOMERA_h
#define ENERGOMERA_h

#include "ESPMDDEVICE.H"

#ifdef ENERGOMERA
/*  #include <Arduino.h>
  #include <IRremoteESP8266.h>
  #include <ESP8266WebServer.h>
  #include <ESP8266HTTPClient.h>
  #include "ESPEEPROM.h"

  extern ESP8266WebServer server; // веб сервер
  extern HTTPClient http; // веб клиент
*/


#include <SoftwareSerial.h>

extern long Previous ; 
extern int Step;
//extern char x [50];

// открываем сессию
extern byte CmdOpenSesion[];
// читаем тип счетчика
extern byte CmdReadType[];
// снимаем показания
extern byte CmdEtope[];
//напряжение на фазах
extern byte CmdVolta[];
// мощность
extern byte CmdPower[];
// частота  
extern byte CmdFrequ[];
// ток  
extern byte CmdCurre[];
// cos f  
extern byte CmdCos_f[];


#define CYCLE_TIME 15
#define DIR 15 

extern String ReadStr;

extern struct Energomera{
    String NameParam;
    String StrValue;
    float  FloatValue;
  }Etope, Volta, Power, Curre, Frequ, Cos_f; 
   
/*extern struct Energomera Etope;
Energomera Volta;
Energomera Power;
Energomera Curre;
Energomera Frequ;
Energomera Cos_f1;
*/

void ValueParser(String inString, String Param, struct Energomera* Buffer);
void EnergomeraInit(); 
void PrintVolume(Energomera* Buffer);
void EnergomeraRead();
void SendCommand(byte* cmd, int size);
void EmergomeraWrite();
void EnergomeraCycle();

#endif
#endif
