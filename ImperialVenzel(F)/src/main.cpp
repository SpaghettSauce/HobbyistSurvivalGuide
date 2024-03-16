/*
что надо сделать:
  1.Шлюз
  2.Светилка если мы в опасной зоне
  3.Система урона
  3.Система жизней
  3.2 Система смерти           <-- звучит страшно не зная контекста
*/


//везде где ... напиши код сам :)
#include <Arduino.h>
#include "function.h"
#include <Servo.h>

#define LifeLight1 12
#define LifeLight2 11
#define LifeLight3 10//пины, пины, пины...

#define DangerLight1 13
#define DangerLight2 3

#define PHS A0
#define Buzzer 8
#define POT A1

int lives = 3; //сколько у нас максимально жизней 

Servo Servik;

void setup()
{
  Serial.begin(9600);
  //сюда подключаем всё что у нас есть
  //...
}

void loop()
{
  
  Servik.write(angleMove(POT));

  //здесь вызываем функиию системы жизней
  //а тут урона

  if (/*что-то с углом*/)
  {
    //пусть мигают светодиоды опасности (красные)
  }
}