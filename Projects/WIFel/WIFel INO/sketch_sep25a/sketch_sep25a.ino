#include <Servo.h>
#define BUT1 7
Servo Servik;


void setup() {

  Servik.attach(8);
  pinMode(BUT,INPUT_PULLUP);

}

void loop() {
  boolean butisup = digitalRead(BUT);

  if(butisup) {
    Servik.write(180);
    delay(200);
    Servik.write(0);
  }
        

}
