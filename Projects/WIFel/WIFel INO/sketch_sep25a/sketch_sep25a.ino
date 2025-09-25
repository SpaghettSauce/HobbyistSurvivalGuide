#include <Servo.h>

#define PERIOD 500
#define MAX 180.0
#define BUT1 7

uint32_t time;

Servo ServikR;
Servo ServikL;

void setup() {

  ServikR.attach(8);
  ServikL.attach(9);
  pinMode(BUT,INPUT_PULLUP);

}

void loop() {
  boolean butisup = digitalRead(BUT);

  if(butisup) {

    if (millis() - time >= PERIOD) {  /
    time = millis();          
    ServikR.write(180);
    ServikL.write(0);
    }
    butisup = !butisup;
  }
        

}
