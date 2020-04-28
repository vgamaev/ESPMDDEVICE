#include "ENERGOMERA.h"

#ifdef ENERGOMERA

EnergomeraStruct Etope, Volta, Power, Frequ, Curre, Cos_f, Etope_old, Volta_old, Power_old, Frequ_old, Curre_old, Cos_f_old;

SoftwareSerial UART(14, 12);  //(RX_EM, TX_EM); //(14, 12)  RX, TX

void EnergomeraInit()
{ 
    UART.begin(9600);
    pinMode(DIR, OUTPUT);
    digitalWrite(DIR, HIGH);
    VersionCode += VersionEnergomera ;
}


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

void IfNullValue(EnergomeraStruct *Buffer, EnergomeraStruct *Buffer_old)
{
  if(Buffer->FloatValue == 0)
  {
    Buffer->FloatValue = Buffer_old->FloatValue ;
    Buffer->StrValue = Buffer_old->StrValue ;
  }
  Buffer_old->FloatValue = Buffer->FloatValue ;
  Buffer_old->StrValue = Buffer->StrValue ;
}

void SendMDEnergomera(EnergomeraStruct *Buffer)
{
    String post = "http://"+Config.serverIP+"/objects/?object="+Config.name+"&op=set&p="+Buffer->NameParam+"&v="+Buffer->FloatValue;
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
              IfNullValue(&Etope, &Etope_old);
              SendMDEnergomera(&Etope);
        break;
        case 4:
              ValueParser(ReadStr, "VOLTA", &Volta);
              PrintVolume(&Volta);
              IfNullValue(&Volta, &Volta_old);
              SendMDEnergomera(&Volta);
        break;
        case 5:
              ValueParser(ReadStr, "POWEP", &Power);
              PrintVolume(&Power);
              IfNullValue(&Power, &Power_old);
              SendMDEnergomera(&Power);
        break;
        case 6:
              ValueParser(ReadStr, "FREQU", &Frequ);
              PrintVolume(&Frequ);
              IfNullValue(&Frequ, &Frequ_old);
              SendMDEnergomera(&Frequ);
        break;
        case 7:
              ValueParser(ReadStr, "CURRE", &Curre);
              PrintVolume(&Curre);
              IfNullValue(&Curre, &Curre_old);
              SendMDEnergomera(&Curre);
        break;
        case 8:
              ValueParser(ReadStr, "COS_f", &Cos_f);
              PrintVolume(&Cos_f);
              IfNullValue(&Cos_f, &Cos_f_old);
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
    
    //ReadStr = "FREQU(50.00)";
      
    if (millis() - Previous > 1000)
    {
     Previous = millis();      
     EnergomeraRead();
     Step ++;
     EmergomeraWrite();          
     }
}

#endif
