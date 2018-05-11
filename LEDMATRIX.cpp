#include "LEDMATRIX.h"

//192.168.1.142/informer?token=esp8266&bright=10&string=привет

#ifdef LED_MATRIX

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

String utf8rus(String source)
{
  int i,k;
  String target;
  unsigned char n;
  char m[2] = { '0', '\0' };

  k = source.length(); i = 0;

  while (i < k) {
    n = source[i]; i++;

    if (n >= 0xC0) {
      switch (n) {
        case 0xD0: {
          n = source[i]; i++;
          if (n == 0x81) { n = 0xA8; break; }
//          if (n >= 0x90 && n <= 0xBF) n = n + 0x30;
          if (n >= 0x90 && n <= 0xBF) n = n + 0x2F;
          break;
        }
        case 0xD1: {
          n = source[i]; i++;
          if (n == 0x91) { n = 0xB8; break; }
//          if (n >= 0x80 && n <= 0x8F) n = n + 0x70;
          if (n >= 0x80 && n <= 0x8F) n = n + 0x6F;
          break;
        }
      }
    }
    m[0] = n; target = target + String(m);
  }
return target;
}

void LedMatrixInit() {
  //Отображакм при имя wifi потключенной сети или точки доступа и ip адрес
  if(Config.ap == "on"){
    tape = "AP-SSID:" + ssid1 + "   AP-IP:" + Config.ipap ;
  }else
  {
    tape = "WIFI SSID:" + Config.ssid + " IP:" + Config.ip ;
  }
  
  matrix.setIntensity(7); // Use a value between 0 and 15 for brightness
  
  // Adjust to your own needs
  matrix.setPosition(0, 3, 0); // The first display is at <0, 0>
  matrix.setPosition(1, 2, 0); // The second display is at <1, 0>
  matrix.setPosition(2, 1, 0); // The third display is at <2, 0>
  matrix.setPosition(3, 0, 0); // And the last display is at <3, 0>
//  ...
  matrix.setRotation(0, 3);    // The first display is position upside down
  matrix.setRotation(1, 3);    // The first display is position upside down
  matrix.setRotation(2, 3);    // The first display is position upside down
  matrix.setRotation(3, 3);    // The same hold for the last display
}

void LedMatrix() {
  
  //tape=utf8rus("Проверка информера: Сегодня наступило лето, температура на улице  +22С и солнышко.");

  for ( int i = 0 ; i < width * tape.length() + matrix.width() - 1 - spacer; i++ ) {

    matrix.fillScreen(LOW);

    int letter = i / width;
    int x = (matrix.width() - 1) - i % width;
    int y = (matrix.height() - 8) / 2; // center the text vertically

    while ( x + width - spacer >= 0 && letter >= 0 ) {
      if ( letter < tape.length() ) {
        matrix.drawChar(x, y, tape[letter], HIGH, LOW, 1);
      }
      letter--;
      x -= width;
    }
    matrix.write(); // Send bitmap to display
    delay(wait);
  }
}

//Обрабатываем ВЕБ запросы
void handleLedMatrix()
{
    String buf = server.arg("token");
    Serial.println(buf);
  
    if (Config.www_password != buf) {
      String message = "access denied";
      server.send(401, "text/plain", message);
      return;
    }
    buf = server.arg("bright");
    char b[3];
    buf.getBytes((unsigned char *)b, 3);
    Serial.print("LED MATRIX bright ");
    Serial.println(StrToULong(b));
    matrix.setIntensity(StrToULong(b)); 
    
    buf = server.arg("string");
    Serial.print("LED MATRIX sring:  ");
    Serial.println(buf);
    tape=utf8rus(buf);
    
    String message = "success";
    server.send(200, "text/plain", message);  
}

#endif

