#ifndef BUTTON_h
#define BUTTON_h

#include "ESPMDDEVICE.H"

#ifdef BUTTON2

#include <Arduino.h>

extern int ButtonPin2[]; // "Ловим" выключатель через GPIO0
extern int can_toggle2[];
extern int button_state2[];

void ButtonRead2();
void ButtonSwitch2();

#endif
#endif
