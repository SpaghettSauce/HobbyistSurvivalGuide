#include <Octofet.h>

#define pump1_1 11
#define pump1_2 10

#define pump2_1 13
#define pump2_2 12

#define pump3_1 9 
#define pump3_2 8

#define pump4_1 7
#define pump4_2 6

#define valve1 0
#define valve2 1
#define valve3 2
#define valve4 3
#define valve5 4
#define valve6 5
#define valve7 6
#define valve8 7

constexpr auto pinCS1 = 5;
constexpr auto pinCS2 = 4;

Octofet octofet(pinCS1);


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


void loop() {
  delay(1000);
 //Сними комментарий с части которую нужно очистить
/*
    octofet.digitalWrite(valve1,HIGH);
    analogWrite(pump1_1, 0);
    analogWrite(pump1_2,255);
  */
  /*
    octofet.digitalWrite(valve2,HIGH);
    analogWrite(pump2_1, 0);
    analogWrite(pump2_2, 255);
*/
/*
    octofet.digitalWrite(valve3,HIGH);
    analogWrite(pump3_1, 0);
    analogWrite(pump3_2,255);
  */
  /*
    octofet.digitalWrite(valve4,HIGH);
    analogWrite(pump4_1, 0);
    analogWrite(pump4_2, 255);
*/
    
  delay(100);
  Serial.println("i'm done");
}
