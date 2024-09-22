#include <Arduino.h>
int val;
int LED = 10; 



void setup() {
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
  digitalWrite(LED,HIGH);
  pinMode(0, INPUT_PULLUP);
}

void loop() {
  if (Serial.available())
  {
    val = Serial.read();
    if (val == '1')
    {
      digitalWrite(LED,HIGH);
    }
    if (val == '0')
    {
      digitalWrite(LED,LOW);
    }
  }

}
