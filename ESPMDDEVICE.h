//#define IR_RESIVER
//#define ADC


//#define Sonoff_Touch
//#define Sonof_T1_2_button
#define Sonof_T1_3_button

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
