#include "ESPIR.h"

IRrecv irrecv(RECV_PIN);
IRsend irsend(SEND_PIN); 

decode_results results;

void IRResiver()
{ 
  if (irrecv.decode(&results)) {
      Serial.println(results.value); //, HEX);
      String post = "http://"+Config.serverIP+"/objects/?object="+Config.name+"&op=m&m=IR_Decode&"+Config.property+"="+results.value;
      //String post = "http://"+Config.serverIP+"/objects/?object="+Config.name+"&op=set&p="+Config.property+"&v="+results.value;
      Serial.println(post);
      http.begin(post);
      int httpCode = http.GET(); 
      http.end();
      irrecv.resume(); // Receive the next value
    }
}

void IRTransmiter()
{
   irsend.sendSAMSUNG(0xE0E0F00F,32);
}

void StartIR()
{
  irrecv.enableIRIn(); // Start the receiver
  irsend.begin();       // Start transmiter
}


