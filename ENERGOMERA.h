#ifndef ENERGOMERA_h
#define ENERGOMERA_h

#include "ESPMDDEVICE.H"

#ifdef ENERGOMERA
  
#include <SoftwareSerial.h>
#include <ESP8266HTTPClient.h>
#include "ESPEEPROM.h"

extern HTTPClient http; // веб клиент

extern String VersionCode;
extern String VersionEnergomera ;

extern long Previous ; 
extern int Step ;

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

extern struct EnergomeraStruct{
    String NameParam;
    String StrValue;
    float  FloatValue;
  }Etope, Volta, Power, Curre, Frequ, Cos_f, Etope_old, Volta_old, Power_old, Curre_old, Frequ_old, Cos_f_old; 


void EnergomeraInit(); 
void ValueParser(String inString, String Param, struct EnergomeraStruct* Buffer);
void PrintVolume(EnergomeraStruct* );
void SendMDEnergomera(EnergomeraStruct *Buffer);
void EnergomeraRead();
void SendCommand(byte* cmd, int size);
void EmergomeraWrite();
void EnergomeraCycle();
void IfNullValue(EnergomeraStruct *Buffer, EnergomeraStruct *Buffer_old);

#endif
#endif
