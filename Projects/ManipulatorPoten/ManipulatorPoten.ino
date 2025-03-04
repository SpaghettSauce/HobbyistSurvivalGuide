#include <Servo.h>
#define max_angle 180.0
Servo Serveek;
Servo Servekle;
Servo Servewys;
Servo Serveper;
void setup() {
  // put your setup code here, to run once:
  Serveek.attach(2);
  Servekle.attach(3);
  Servewys.attach(4);
  Serveper.attach(5);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
int val = analogRead(A0);
int angle = int(val/1024.0 * max_angle);
angle = constrain(angle,0,180);
Serveek.write(angle);

int gal = analogRead(A1);
int gangle = int(gal/1024.0 * max_angle);
gangle = constrain(gangle,0,180);
Servekle.write(gangle);

int tal = analogRead(A2);
int tangle = int(tal/1024.0 * max_angle);
tangle = constrain(tangle,0,180);
Serial.println(tangle);
Servewys.write(tangle);

int hal = analogRead(A3);
int langle = int(hal/1024.0 * max_angle);
langle = constrain(langle,0,180);
Serveper.write(langle);
}
