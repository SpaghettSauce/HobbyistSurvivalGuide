#pragma once
#include "function.h"
void firelight(int pin){
    analogWrite(pin,85);
    delay(1000);
    analogWrite(pin,0);
    delay(1000);
}