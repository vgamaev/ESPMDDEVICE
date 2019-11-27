#include "BUTTON.h"

#ifdef BUTTON2

// Инециализируем входы для кнопок
void ButtonInit2()
{
   ButtonPin2[0]=0;  //def 0 15 16 13 6 7 4 3 2 1
   //ButtonPin2[1]=9;
   //ButtonPin2[2]=10;
     
  // Назначаем пины и их режимы.
   for(int i=0; i<MAX_BUTTON2; i++ ) 
   {
      pinMode(ButtonPin2[i], INPUT_PULLUP);
      can_toggle2[i]=0;
      button_state2[i]=0;
   }
}



// Проверяем нажатие кнопок выключателя
void ButtonRead2()
{
  for(int i=0; i<MAX_BUTTON2; i++) button_state2[i] = digitalRead(ButtonPin2[i]);
}

//Отрабатываем однократно нажатую клавишу
void ButtonIsPressedOnce(int nomer)
{
  #ifdef BUTTON2
      KarnizButtonSwitch(nomer);
  #endif
}

// Обрабатываем нажатие кнопок
void ButtonSwitch2()
{
  // Проверяем нажатие кнопок выключателя
  ButtonRead2();
  for(int i=0; i<MAX_BUTTON2; i++)
  {
    if(button_state2[i] == HIGH && can_toggle2[i]) {
      ButtonIsPressedOnce(i);
      can_toggle2[i] = false;
      delay(500);
    }else if (button_state2[i] == LOW) {
      can_toggle2[i] = true;
    }
  }
}

#endif
