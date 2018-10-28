#include "ADC.h"

#ifdef ADC

void adcRead()
{
    static long previousMillis = 0;                             
    long currentMillis = millis();
     
    if(currentMillis - previousMillis > 1000) 
    {
      previousMillis = currentMillis;    
      adcValue = map(analogRead(A0), 1022, 0, 0,100);
      float DeltaPlus = adcValueOld + 2;
      float DeltaMinus = adcValueOld - 2;
      if(adcValue < DeltaMinus ||  adcValue > DeltaPlus)
      //if(adcValue != adcValueOld)
      { 
        String post = "http://"+Config.serverIP+"/objects/?object="+Config.name+"&op=set&p=ADC&v="+adcValue;
        Serial.println(post);
        http.begin(post);
        int httpCode = http.GET(); 
        http.end();
        adcValueOld = adcValue;
      }
    }
}
#endif

