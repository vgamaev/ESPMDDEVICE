//#define IR_RESIVER   //Собиракм ИК ресивер
//#define ADC          // Мерим освещеность фоторезистором
#define WIFI_LED       // Светодиод сети Wi-Fi
//#define LED_MATRIX       // Информер на светодиодных матрицах MAX7219
//#define RF433MHZ
//#define DHT22            // Датчик температуры и влажности DHT22
#define KARNIZ           // Управление эдектрокарнизом
//#define BUTTON           // Включаем кнопки
#define BUTTON           // Включаем кнопки версии 2
#define WEBUPDATE        // Будет работать только с ESP8266 с большим чем 1Мб встроеной флеш памяти

//#define RELAYS_ON      //Собираем выключатели, не рекомендую вместе с #define IR_RESIVER

//#define Sonoff_Touch          //Подходит и для розетки Sonoff S20 примечание ниже
//#define Sonof_T1_2_button
//#define Sonof_T1_3_button

#ifdef Sonoff_Touch
  #define MAX_RELAY  1
  #define MAX_BUTTON 1
#endif

#ifdef Sonof_T1_2_button
  #define MAX_RELAY  2
  #define MAX_BUTTON 2
#endif

#ifdef Sonof_T1_3_button
  #define MAX_RELAY  3
  #define MAX_BUTTON 3
#endif

#ifdef BUTTON
  #define MAX_BUTTON2 2
#endif

/* При компиляции для выключателей Sonoff выбераем Generic ESP8285 Module
 *  При компиляции для выключателя Sonoff s20 с флеш памятью PN25F08B выбераем Generic ESP8266 Module 
 *  flash mode DOUT, flash size 1M(64K SPIFFS)
 *  https://letscontrolit.com/forum/viewtopic.php?t=3071
 */
