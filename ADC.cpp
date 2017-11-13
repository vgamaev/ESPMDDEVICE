#include "ADC.h"


void adcRead()
{
    static long previousMillis = 0;                             
    long currentMillis = millis();
     
    if(currentMillis - previousMillis > 1000) 
    {
      previousMillis = currentMillis;    
      adcValue = map(analogRead(A0), 1022, 0, 0,100);
      //if(adcValue < adcValueOld - 5 ||  adcValue > adcValueOld + 5)
      if(adcValue != adcValueOld)
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

