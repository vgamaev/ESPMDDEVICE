#include "ESPIR.h"

#ifdef IR_RESIVER
//http://192.168.1.138/ir?token=esp18266&ircode=3772818013
//http://192.168.1.139/on?token=esp8266

IRrecv irrecv(RECV_PIN);
IRsend irsend(SEND_PIN); 

decode_results results;

/* unsigned long StrToULong(char *str)
{
 int len = strlen(str);
 unsigned long res = 0;
 unsigned long mul = 1;
 for(int i = len - 1; i >= 0; i--){
  res += mul * (unsigned long)(str[i] - '0');
  mul *= 10;
 }
 return res;
} */

// Получаем от сервера MD команду включить
void handleIR() {
  String buf = server.arg("token");
  Serial.println(buf);
//  Serial.println("poken");

  if (Config.www_password != buf) {
    String message = "access denied";
    server.send(401, "text/plain", message);
    return;
  }
  buf = server.arg("ircode");
  Serial.println(buf);
  char b[32];
  //buf.getBytes(b, 32);
  buf.getBytes((unsigned char *)b, 32);
  Serial.println(StrToULong(b));
  IRTransmiter(StrToULong(b));
  String message = "success";
  server.send(200, "text/plain", message);
}

void IRResiver()
{ 
  if (irrecv.decode(&results)) {
      Serial.println(results.value); //, HEX);
      //String post = "http://"+Config.serverIP+"/objects/?object="+Config.name+"&op=m&m=IR_Decode&"+Config.property+"="+results.value;
      String post = "http://"+Config.serverIP+"/objects/?object="+Config.name+"&op=set&p="+Config.property+"&v="+results.value;
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
}

#endif
