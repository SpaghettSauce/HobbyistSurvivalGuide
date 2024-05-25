#include <Arduino.h>
#include "function.h"
#define LED 3

void setup() {
  pinMode(LED,OUTPUT);
}

void loop() {
  firelight(LED);
}