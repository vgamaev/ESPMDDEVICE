#include "ENERGOMERA.h"

#ifdef ENERGOMERA

EnergomeraStruct Etope, Volta, Power, Frequ, Curre, Cos_f;

SoftwareSerial UART(14, 12);  //(RX_EM, TX_EM); //(14, 12)  RX, TX

void EnergomeraInit()
{ 
    UART.begin(9600);
    pinMode(DIR, OUTPUT);
    digitalWrite(DIR, HIGH);
}
/*
struct EnergomeraStruct{
    String NameParam;
    String StrValue;
    float  FloatValue;
  }Etope, Volta, Power, Curre, Frequ, Cos_f; 
   */


void ValueParser(String inString, String Param, EnergomeraStruct* Buffer)
{
  char x [50];
  String inString2;
  //struct Energomera Buffer;

  Buffer->NameParam = Param;
  Buffer->StrValue = "0";
  Buffer->FloatValue = 0;

  if (inString.lastIndexOf(Param)>0) 
      {
          int first = inString.indexOf(Param);
          first = inString.indexOf('(', first + 1 );
          first = first +1;
          //Serial.println(first);
          int first_2 = inString.indexOf(')', first + 1 );
                   
          inString2 = inString.substring(first,first_2);
          inString2.toCharArray(x, sizeof(x));
          float f = atof(x);
          
          Buffer->StrValue = inString2;
          Buffer->FloatValue = f;
          
          inString = "";
      }
      //return Buffer;
}

void PrintVolume(EnergomeraStruct *Buffer)
{
   Serial.print(Buffer->NameParam); 
   Serial.print("   ");
   Serial.print(Buffer->StrValue);   //формат string
   Serial.print("------>");
   Serial.println(Buffer->FloatValue);           //формат float
}

void SendMDEnergomera(EnergomeraStruct *Buffer)
{
    String post = "http://"+Config.serverIP+"/objects/?object="+Config.name+"&op=set&p="+Buffer->NameParam+"&v="+Buffer->StrValue;
    Serial.println(post);
    http.begin(post);
    int httpCode = http.GET(); 
    http.end();
}

void EnergomeraRead()
{
  switch (Step) {
        case 1:
              
        break;
        case 2:
              
        break;
        case 3:
              ValueParser(ReadStr, "ET0PE", &Etope);
              PrintVolume(&Etope);
              SendMDEnergomera(&Etope);
        break;
        case 4:
              ValueParser(ReadStr, "VOLTA", &Volta);
              PrintVolume(&Volta);
              SendMDEnergomera(&Volta);
        break;
        case 5:
              ValueParser(ReadStr, "POWEP", &Power);
              PrintVolume(&Power);
              SendMDEnergomera(&Power);
        break;
        case 6:
              ValueParser(ReadStr, "FREQU", &Frequ);
              PrintVolume(&Frequ);
              SendMDEnergomera(&Frequ);
        break;
        case 7:
              ValueParser(ReadStr, "CURRE", &Curre);
              PrintVolume(&Curre);
              SendMDEnergomera(&Curre);
        break;
        case 8:
              ValueParser(ReadStr, "COS_f", &Cos_f);
              PrintVolume(&Cos_f);
              SendMDEnergomera(&Cos_f);
              Serial.println();
        break;
        default:
  
        break;
      }
      ReadStr = "";
}


void SendCommand(byte* cmd, int size)
{
    digitalWrite(DIR, HIGH);
    UART.write (cmd,size);
    digitalWrite(DIR, LOW);
}

void EmergomeraWrite()
{
    switch (Step) {
        case 1:
             SendCommand(CmdOpenSesion,5);
        break;
        case 2:
             SendCommand(CmdReadType,6);
        break;
        case 3:
             SendCommand(CmdEtope,13);
        break;
        case 4:
             SendCommand(CmdVolta,13);
        break;
        case 5:
             SendCommand(CmdPower,13);
        break;
        case 6:
             SendCommand(CmdFrequ,13);
        break;
        case 7:
             SendCommand(CmdCurre,13);
        break;
        case 8:
             SendCommand(CmdCos_f,13);
        break;
        case CYCLE_TIME:
               Step = 0;
        break;
          default:
  
        break;
      }
     
}


void EnergomeraCycle()
{ 
  if (UART.available())
    {
      char response = UART.read();
      response &= 0x7F;// convert 8N1 to 7E1
      
      Serial.print(response);
      char inChar = response;

      ReadStr += inChar;
    }
    
    ReadStr = "FREQU(50.00)";
      
    if (millis() - Previous > 1000)
    {
     Previous = millis();      
     EnergomeraRead();
     Step ++;
     EmergomeraWrite();          
     }
}

#endif
