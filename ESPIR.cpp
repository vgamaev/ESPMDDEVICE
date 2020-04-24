#include "ESPIR.h"

#ifdef IR_RESIVER
//http://192.168.1.138/ir?token=esp18266&ircode=3772818013
//http://192.168.1.139/on?token=esp8266

IRrecv irrecv(RECV_PIN);
IRsend irsend(SEND_PIN); 

decode_results results;

// Получаем от сервера MD команду включить
void handleIR() {
  String buf = server.arg("token");
  Serial.println(buf);
  if (Config.www_password != buf) {
    String message = "access denied";
    server.send(401, "text/plain", message);
    return;
  }
  buf = server.arg("ircode");
  Serial.println(buf);
  char b[32];
  //long a = StrToULong(b);  //Проверить
  //buf.getBytes(b, 32);
  buf.getBytes((unsigned char *)b, 32);
  Serial.println(StrToULong(b));
  IRTransmiter(StrToULong(b));
  TransmiterCode = b;
  String message = "success";
  server.send(200, "text/plain", message);
}

void IRResiver()
{ 
  if (irrecv.decode(&results)) {
      // print() & println() can't handle printing long longs. (uint64_t)
//      serialPrintUint64(results.value, DEC);
      ResiverCode = uint64ToString(results.value, DEC);
      Serial.println(ResiverCode); //, HEX);
      //String post = "http://"+Config.serverIP+"/objects/?object="+Config.name+"&op=m&m=IR_Decode&"+Config.property+"="+results.value;
      String post = "http://"+Config.serverIP+"/objects/?object="+Config.name+"&op=set&p="+Config.property+"&v="+ResiverCode;
      Serial.println(post);
      http.begin(post);
      int httpCode = http.GET(); 
      http.end();
      irrecv.resume(); // Receive the next value
    }
}

void IRTransmiter(unsigned long SendIRCode)
{
   //irsend.sendSAMSUNG(0xE0E0F00F,32);
   Serial.println(SendIRCode);
   irsend.sendSAMSUNG(SendIRCode,32);
}

void StartIR()
{
  irrecv.enableIRIn(); // Start the receiver
  irsend.begin();       // Start transmiter
  VersionCode += VersionIrResiver ;
}

#endif
