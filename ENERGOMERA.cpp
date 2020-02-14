#include "ENERGOMERA.h"

#ifdef ENERGOMERA

Energomera ValueParser(String inString, String Param)
{
  String inString2;
  Energomera Buffer;

  Buffer.NameParam = Param;
  Buffer.StrValue = "0";
  Buffer.FloatValue = 0;

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
          
          Buffer.StrValue = inString2;
          Buffer.FloatValue = f;
          
          inString = "";
      }
      return Buffer;
}

void PrintVolume(Energomera Buffer)
{
   Serial.print(Buffer.NameParam); 
   Serial.print("   ");
   Serial.print(Buffer.StrValue);   //формат string
   Serial.print("------>");
   Serial.println(Buffer.FloatValue);           //формат float
}

void EnergomeraRead()
{
  switch (Step) {
        case 1:
              
        break;
        case 2:
              
        break;
        case 3:
              Etope = ValueParser(ReadStr, "ET0PE");
              PrintVolume(Etope);
        break;
        case 4:
              Volta = ValueParser(ReadStr, "VOLTA");
              PrintVolume(Volta);
        break;
        case 5:
              Power = ValueParser(ReadStr, "POWEP");
              PrintVolume(Power);
        break;
        case 6:
              Frequ = ValueParser(ReadStr, "FREQU");
              PrintVolume(Frequ);
        break;
        case 7:
              Curre = ValueParser(ReadStr, "CURRE");
              PrintVolume(Curre);
        break;
        case 8:
              Cos_f = ValueParser(ReadStr, "COS_f");
              PrintVolume(Cos_f);
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
      
      //Serial.print(response);
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
