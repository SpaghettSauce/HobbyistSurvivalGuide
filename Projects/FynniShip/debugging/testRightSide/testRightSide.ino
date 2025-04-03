#include <Octofet.h>


#define pump1_1 11
#define pump1_2 10

#define pump2_1 9
#define pump2_2 8

#define pump3_1 7 
#define pump3_2 6

#define pump4_1 4
#define pump4_2 3

#define valve1 0
#define valve2 1
#define valve3 2
#define valve4 3
#define valve5 4
#define valve6 5
#define valve7 6
#define valve8 7

constexpr auto pinCS1 = 5;
constexpr auto pinCS2 = 12;

Octofet octofet(pinCS1);
Octofet octofet1(pinCS2);

void setup() {
  octofet.begin();

  pinMode(pump1_1, OUTPUT);
  pinMode(pump1_2,OUTPUT);

  pinMode(pump2_1, OUTPUT);
  pinMode(pump2_2,OUTPUT);

  pinMode(pump3_1, OUTPUT);
  pinMode(pump3_2,OUTPUT);

  pinMode(pump4_1, OUTPUT);
  pinMode(pump4_2,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // К1 -> Н1 -> БЦ1 (10 СЕК) -> K5 -> Н3 -> БЦ3 -> AGAIN
 

    octofet.digitalWrite(valve1,HIGH);
    analogWrite(pump3_1, 255);
    analogWrite(pump3_2,0);
    delay(10000);
    octofet.digitalWrite(valve1,LOW);
    analogWrite(pump3_1, 0);
    analogWrite(pump3_2, 0);
    delay(100);
    octofet.digitalWrite(valve5,HIGH);
    analogWrite(pump3_1, 0);
    analogWrite(pump3_2,255);
    delay(10000);
  octofet.digitalWrite(valve5,LOW);


  delay(100);
  Serial.println("i'm done");
}
