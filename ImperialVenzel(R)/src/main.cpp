/*1.Шлюз
  2.Danger light
  3.Damage control
  3.1 life system + reaction
  3.2 immunity system
*/
#include <Arduino.h>
#include "function.h"
#include <Servo.h>

#define LifeLight1 12
#define LifeLight2 11
#define LifeLight3 10

#define DangerLight1 13
#define DangerLight2 3

#define PHS A0
#define Buzzer 8
#define POT A1
#define MaxLives 3

unsigned long startingTime;
unsigned long duration = 3000;
int lives = MaxLives;

int LifePins[] = {LifeLight1, LifeLight2, LifeLight3};
Servo Servik;

void setup()
{
  Serial.begin(9600);
  startingTime = millis();
  Servik.attach(9);

  pinMode(Buzzer, OUTPUT);
  pinMode(DangerLight1, OUTPUT);
  pinMode(DangerLight2, OUTPUT);
  pinMode(LifeLight1, OUTPUT);
  pinMode(LifeLight2, OUTPUT);
  pinMode(LifeLight3, OUTPUT);
  pinMode(POT, INPUT);
}

void loop()
{
  while (lives > 0 ){
    int angle = angleMove(POT);
    Servik.write(angle);
    Serial.println(lives);
    lifeSystem(MaxLives, LifePins, lives/*lives,LifeLight1,LifeLight2,LifeLight3*/);
    damageControl(lives, PHS, startingTime, duration, Buzzer);
  }
  Serial.println("Whoopsy Daisy");
  digitalWrite(LifeLight1,LOW);
  for (int i=0; i<5; i++)
  {
    tone(Buzzer,900,200);
    delay(150);
  }
}