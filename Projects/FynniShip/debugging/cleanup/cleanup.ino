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

constexpr auto pinCS1 = 5;
//constexpr auto pinCS2 = 4;

Octofet octofet(pinCS1);
//Octofet octofet1(pinCS2);


void setup() {
  octofet.begin();
 // octofet1.begin();

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
/*
    octofet.digitalWrite(valve1,HIGH);
    analogWrite(pump1_1, 0);
    analogWrite(pump1_2,255);
  */
  /*
    octofet.digitalWrite(valve2,HIGH);
    analogWrite(pump2_1, 255);
    analogWrite(pump2_2, 0); //выкачка
*/
/*
    octofet.digitalWrite(valve3,HIGH);
    analogWrite(pump3_1, 0);
    analogWrite(pump3_2,255);
*/  
  
    octofet.digitalWrite(valve4,HIGH);
    analogWrite(pump4_1, 255);
    analogWrite(pump4_2, 0);

    
  delay(100);
  Serial.println("i'm done");
}