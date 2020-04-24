#include "RF433MHZ.h"

#ifdef RF433MHZ

RCSwitch mySwitch = RCSwitch();

void Resiver433()
{ 
  //Serial.print("433 ");
  if (mySwitch.available()) {
      code433=mySwitch.getReceivedValue();
      Serial.print("433 MHZ Received code: ");
      Serial.println(code433); //, HEX);
      //String post = "http://"+Config.serverIP+"/objects/?object="+Config.name+"&op=m&m=IR_Decode&"+Config.property+"="+results.value;
      String post = "http://"+Config.serverIP+"/objects/?object="+Config.name+"&op=set&p="+Config.property+"&v="+code433;
      Serial.println(post);
      http.begin(post);
      int httpCode = http.GET(); 
      http.end();
      mySwitch.resetAvailable();
    }
}

void Start433()
{
  mySwitch.enableReceive(2);  // Receiver on interrupt 0 => that is pin #2
  //Serial.print("Init 433 ");
  VersionCode += Version433MHz ;
}

#endif
