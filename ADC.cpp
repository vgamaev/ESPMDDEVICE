#include "ADC.h"

#ifdef ADC

void adcRead()
{
    static long previousMillis = 0;                             
    long currentMillis = millis();
     
    if(currentMillis - previousMillis > ADCInterval) 
    {
      previousMillis = currentMillis;  
        
      #ifdef FOTOREZ
      adcValue = map(analogRead(A0), 1022, 0, 0,100);
      #endif

      #ifdef MQ135
        adcValue = map(analogRead(A0), 330, 430, 0,100);   //adcValue = analogRead(A0);
      #endif
      
      float DeltaPlus = adcValueOld + 2;
      float DeltaMinus = adcValueOld - 2;
      if(adcValue < DeltaMinus ||  adcValue > DeltaPlus)
      //if(adcValue != adcValueOld)
      { 
        String post = "http://"+Config.serverIP+"/objects/?object="+Config.name+"&op=set&p=ADC&v="+adcValue;
        Serial.println(post);
        http.begin(client, post);
        int httpCode = http.GET(); 
        http.end();
        adcValueOld = adcValue;
      }
    }
}

void ADCInit()
{
  VersionCode += VersionADC ;
 }

#endif
