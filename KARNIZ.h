#ifndef KARNIZ_h
#define KARNIZ_h

#include "ESPMDDEVICE.H"

#ifdef KARNIZ
  extern int ENA;
  extern int IN1;
  extern int IN2;

  extern int KarnizMotorState;
  extern int KarnizMotorCommand;

  void InitKarniz();
  void MotorForward();
  void MotorBackward(); 
  void MotorStop();

#endif
#endif
