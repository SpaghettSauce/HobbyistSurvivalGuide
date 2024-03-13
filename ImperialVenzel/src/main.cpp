/*1.Шлюз
  2.Danger light
  3.Damage control
  3.1 life system + reaction
  3.2 immunity system
*/
#include <Arduino.h>
#include "function.h"
#include <Servo.h>

#define lifeLight1 12
#define lifeLight2 11
#define lifeLight3 10
#define dangerLight1 13
#define dangerLight2 3
#define PHS A0
#define Buzzer 8 
#define POT A1

unsigned long startingTime;
unsigned long duration = 3000;
int lives = 3;

Servo Servik; 



void setup() {
  Serial.begin(9600);
  startingTime = millis();
  Servik.attach(9);

  pinMode(Buzzer,OUTPUT);
  pinMode(dangerLight1,OUTPUT);
  pinMode(dangerLight2,OUTPUT);
  pinMode(lifeLight1,OUTPUT);                                   
  pinMode(lifeLight2,OUTPUT);
  pinMode(lifeLight3,OUTPUT);
  pinMode(POT,INPUT);
}

void loop() {
  int light = analogRead(PHS);
  Servik.write(angleMove(POT));
  Serial.println(light);
  Serial.print("and now angle ");
  Serial.print(angleMove(POT));

  lifeSystem(lifeLight1,lifeLight2,lifeLight3,lives);

  if (angleMove(POT) >20){ //danger
    digitalWrite(dangerLight1,HIGH);
    digitalWrite(dangerLight2,HIGH);
    delay(300);
    digitalWrite(dangerLight1,LOW);
    digitalWrite(dangerLight2,LOW);
    delay(400);
  }

  if (light >268)
  {
    lives -=1;
    for (int i=0; i<5; i++)
    {
      digitalWrite(lifeLight1,HIGH);
      delay(500);
      digitalWrite(lifeLight1,LOW);
      delay(500);
    }
    digitalWrite(lifeLight1,LOW);
  }

}