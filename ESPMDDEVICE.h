//#define IR_RESIVER
//#define ADC
#define WIFI_LED


#define Sonoff_Touch          //Подходит и для розетки Sonoff S20 примечание ниже
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

/* При компиляции для выключателей Sonoff выбераем Generic ESP8285 Module
 *  При компиляции для выключателя Sonoff s20 с флеш памятью PN25F08B выбераем Generic ESP8266 Module 
 *  flash mode DOUT, flash size 1M(64K SPIFFS)
 */
