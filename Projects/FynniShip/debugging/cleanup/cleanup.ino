#include <Octofet.h>

#define pump1_1 9
#define pump1_2 8

#define pump2_1 11
#define pump2_2 10

#define pump3_1 6
#define pump3_2 7

#define pump4_1 3
#define pump4_2 4

#define valve1 0
#define valve2 1
#define valve3 2
#define valve4 3
#define valve5 4
#define valve6 5
#define valve7 6
#define valve8 7

constexpr auto pinCS = 5;

Octofet octofet(pinCS);

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

 //Сними комментарий с части которую нужно очистить

    octofet.digitalWrite(0,HIGH,0);
    analogWrite(pump1_1, LOW);
    analogWrite(pump1_2,HIGH);
  
  /*
    octofet.digitalWrite(1,HIGH,0);
    analogWrite(pump2_1, LOW);
    analogWrite(pump2_2,HIGH);
*/
/*
    octofet.digitalWrite(2,HIGH,0);
    analogWrite(pump3_1, LOW);
    analogWrite(pump3_2,HIGH);
*/  
  /*
    octofet.digitalWrite(3,HIGH,0);
    analogWrite(pump4_1, LOW);
    analogWrite(pump4_2,HIGH);
*/
    
  Serial.println("i'm done");
}