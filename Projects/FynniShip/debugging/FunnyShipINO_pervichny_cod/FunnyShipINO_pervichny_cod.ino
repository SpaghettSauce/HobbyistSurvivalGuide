#include <Octofet.h>
#include <SPI.h>
#include <Wire.h>
//#include <L3G.h>

#define pump1_1 11
#define pump1_2 10

#define pump2_1 13
#define pump2_2 12

#define pump3_1 9 
#define pump3_2 8

#define pump4_1 7
#define pump4_2 6

#define valve0 0
#define valve1 1
#define valve2 2
#define valve3 3
#define valve4 4
#define valve5 5
#define valve6 6
#define valve7 7

constexpr auto pinCS1 = 5;
constexpr auto pinCS2 = 4;
//L3G gyro;
Octofet octofet(pinCS1);
//Octofet octofet(pinCS2);

void setup() {
  octofet.begin();

  //pinMode(valve,OUTPUT);

  pinMode(pump1_1, OUTPUT);
  pinMode(pump1_2,OUTPUT);

  pinMode(pump2_1, OUTPUT);
  pinMode(pump2_2,OUTPUT);

  pinMode(pump3_1, OUTPUT);
  pinMode(pump3_2,OUTPUT);

  pinMode(pump4_1, OUTPUT);
  pinMode(pump4_2,OUTPUT);
  Serial.begin(9600);

  //if (!gyro.init())//Проверка подключения гироскопа к ардуино 
//  gyro.enableDefault();
}

void loop() {
  
  //gyro.read();

    octofet.digitalWrite(valve0,HIGH);
    analogWrite(pump4_1, 255);
    analogWrite(pump4_2,0);
    delay(10000);
    octofet.digitalWrite(valve0,LOW);
    analogWrite(pump4_1, 0);
    analogWrite(pump4_2, 0);
    delay(100);
    octofet.digitalWrite(valve4,HIGH);
    analogWrite(pump4_1, 0);
    analogWrite(pump4_2,255);
    delay(10000);
  octofet.digitalWrite(valve4,LOW);

    /*octofet.digitalWrite(valve7,HIGH);
    analogWrite(pump4_1, 255);
    analogWrite(pump4_2, 0);
*/
  delay(100);
  Serial.println("i'm done");
}
