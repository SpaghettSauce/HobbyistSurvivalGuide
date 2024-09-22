#include <Arduino.h>

#define motorR 9
#define motorL 10
int val;

void setup() 
{
  Serial.begin(115200);
  pinMode(motorR, OUTPUT);
  pinMode(motorL, OUTPUT);
  pinMode(0, INPUT_PULLUP);
}

void loop() 
{
  int speed = 255; 
  
  if (Serial.available() > 0) 
  {  
    val = Serial.read();          
    Serial.println(val);           
  }

    if (val == 'd') 
    {  // Move to the right
      analogWrite(motorR, speed - 180);
      analogWrite(motorL, speed);
      Serial.println("Moving forward");
    }

    else if (val == 'w') 
    {  // Move forward
      analogWrite(motorR, speed);
      analogWrite(motorL, speed);
      Serial.println("Moving forward");}

    else if (val == 'a') 
    {  // Move to the left
      analogWrite(motorR, speed);
      analogWrite(motorL, speed - 180);
      Serial.println("Moving forward");}

    else if (val == 's') 
    {  // stop
      analogWrite(motorR, -speed);
      analogWrite(motorL, -speed);
      Serial.println("Moving backward");
    } 
    else 
    {
      Serial.println("What does that supposed to mean?");
    }
    
  delay(100);  
}
