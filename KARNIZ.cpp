#include "KARNIZ.h"

#ifdef KARNIZ
#include <Arduino.h>
void InitKarniz() {
  // set all the motor control pins to outputs
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
}
#endif
