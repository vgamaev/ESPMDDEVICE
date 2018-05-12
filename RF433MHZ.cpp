#include "RF433MHZ.h"

#ifdef RF433MHZ

RCSwitch mySwitch = RCSwitch();

void Resiver433()
{ 
  if (mySwitch.available()) {
      unsigned long code=mySwitch.getReceivedValue();
      Serial.print("Received ");
      Serial.println(code); //, HEX);
      //String post = "http://"+Config.serverIP+"/objects/?object="+Config.name+"&op=m&m=IR_Decode&"+Config.property+"="+results.value;
      String post = "http://"+Config.serverIP+"/objects/?object="+Config.name+"&op=set&p="+Config.property+"&v="+code;
      Serial.println(post);
      http.begin(post);
      int httpCode = http.GET(); 
      http.end();
      mySwitch.resetAvailable();
    }
}

void Start433()
{
  mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2
}

#endif