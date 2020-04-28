/* В этом файле собраны переменые при помощи которых можно сконфигурировать например пины, тайминги и т.п */

#include "ESPMDDEVICE.H"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266mDNS.h>
#include "ESPEEPROM.h"
#include "ESPWIFI.h"
#include "ESPWEB.h"
#include "WEBUPDATE.h"


String VersionCode = "Version: ";

#ifdef RF433MHZ
    #include "RF433MHZ.h"
    unsigned long code433 =0;
    Version433MHz = "1.00 RF 433MHZ";
#endif

//==============================================
#ifdef ADC
  #include "ADC.h"
  int adcValue = 0;
  int adcValueOld = 0;
       
  #ifdef FOTOREZ
      long ADCInterval= 1000;
      String VersionADC = " 1.0 FOTOREZ ";
  #endif

  #ifdef MQ135
      long ADCInterval= 60000;
      String VersionADC = " 1.2 MQ135 ";
  #endif
#endif

#ifdef IR_RESIVER
//=== IR Resiver ==============================
  #include "ESPIR.h"
  int RECV_PIN = 5; //an IR detector/demodulatord is connected to GPIO pin 2
  int SEND_PIN = 15; //an IR led is connected to GPIO pin 0
  String ResiverCode = "0";
  String TransmiterCode = "0";
  String VersionIrResiver = "2.05 IR RESIVER";
#endif


#ifdef RELAYS_ON//==== WIFI SWITCH =============================
  #include "LAMP.h"
  int RelayPin[MAX_RELAY];
  int lamp_on[MAX_RELAY];
  int ButtonPin[MAX_BUTTON];
  int can_toggle[MAX_BUTTON];
  int button_state[MAX_BUTTON];
  bool web_button_state[MAX_RELAY];
  String VersionRelay = "2.05 RELAY TESTER";
#endif

#ifdef BUTTON2
//==================Кнопки версии 2=============================
  #include "BUTTON.h"
  int ButtonPin2[MAX_BUTTON2];
  int can_toggle2[MAX_BUTTON2];
  int button_state2[MAX_BUTTON2];
#endif

#ifdef LED_MATRIX
  #include "LEDMATRIX.h"
  int pinCS = 15;                           //   DIN -> GPIO13 (MOSI) SCK -> GPIO14 (SCK) CS -> GPIO15(или любой свободный) Пины задаются в недрах библиотек Max72xxPanel. Я
  int numberOfHorizontalDisplays = 5;       // число матриц 8x8 MAX7219по горизонтали
  int numberOfVerticalDisplays = 1;         // Число матриц по вертикали
  String tapeMatrix;                        // Буфер для принятия строки
  String tape;                              // Буфер для отображения строки
  int wait = 80;                            // In milliseconds
  int spacer = 1;
  int width = 5 + spacer;                   // The font width is 5 pixels
  int MatrixOFF = 0 ;
  int MatrixCounter = 0;                    // Счетчик дляотображения бегущей строки
  String VersionLedMatrix = "2.05 LED MATRIX";
#endif

//==============================================
#ifdef DHT22
  #include "DHT22.h"
  float tempDHT = 0;
  float humDHT = 0;
  float tempDHTOld = 0;
  float humDHTOld = 0;
  float hicDHT = 0;
  String VersionDHT = "1.0 DHT22 ";
#endif

//======================= KARNIZ =================================================
#ifdef KARNIZ
  #include "KARNIZ.h"
  //int ENA = 14;
  int IN1 = 16;
  int IN2 = 14;
  int KarnizMotorState = 0;
  int KarnizLength = 2; //16;
  int CurKarnizPosition = 0;
  int KarnizPosition = 0;
  String VersionKARNIZ = "2.05 KARNIZ";
    
#endif

//======================= ENERGOMERA ===============================================
#ifdef ENERGOMERA
  #include "ENERGOMERA.h"

  /*#define RX_EM 14
  #define TX_EM 12
  #define CYCLE_TIME 15
  #define DIR 15 */
  
  long Previous = 0; 
  int Step = 0;
 
  String ReadStr;
 
  // открываем сессию
   byte CmdOpenSesion[] = {0xaF,0x3F,0x21,0x8D,0x0A};
  // читаем тип счетчика
   byte CmdReadType[] = {0x06,0x30,0x35,0xb1,0x8d,0x0a};
  // снимаем показания
   byte CmdEtope[] = {0x81,0xd2,0xb1,0x82,0xc5,0xd4,0x30,0x50,0xc5,0x28,0xa9,0x03,0xb7};
  //напряжение на фазах
   byte CmdVolta[] = {0x81,0xd2,0xb1,0x82,0x56,0xcf,0xcc,0xd4,0x41,0x28,0xa9,0x03,0x5f};
  // мощность
   byte CmdPower[] = {0x81,0xd2,0xb1,0x82,0x50,0xcf,0xd7,0xc5,0x50,0x28,0xa9,0x03,0xe4};
  // частота  
   byte CmdFrequ[] = {0x81,0xd2,0xb1,0x82,0xc6,0xd2,0xc5,0xd1,0x55,0x28,0xa9,0x03,0x5c};
  // ток  
   byte CmdCurre[] = {0x81,0xd2,0xb1,0x82,0xc3,0x55,0xd2,0xd2,0xc5,0x28,0xa9,0x03,0x5a};
  // cos f  
   byte CmdCos_f[] = {0x81,0xd2,0xb1,0x82,0xc3,0xCF,0x53,0x5F,0x66,0x28,0xa9,0x03,0x03};
  
   String VersionEnergomera = "2.06 ENERGOMERA";
#endif

//=======================Светодиод WIFI=========================================
long WiFiCheckinterval = 1000; //Интервал проверки WiFi потключения
int WIWI_Connect=0;

//#ifdef WIFI_LED
  int WIFI_led = 13;             // Светодиод на выклчателе GPIO13
//#endif

String ssid1;
const char *password1 = "66666666";

ESP8266WebServer server (80) ; // веб сервер
HTTPClient http; // веб клиент

unsigned long StrToULong(char *str);
