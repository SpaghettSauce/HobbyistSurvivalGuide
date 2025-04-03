#include <Octofet.h>
#include <SPI.h>
#include <Wire.h>
//#include <L3G.h>

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
//constexpr auto pinCS2 = 12;
constexpr auto deviceCount = 2;
Octofet octofet(pinCS1,deviceCount);
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
  // 0 -> 1 , 1 -> 0 , 2 -> 1 , 3 -> 1, 
octofet.digitalWrite(0, HIGH, 0);
octofet.digitalWrite(1, HIGH, 0);
octofet.digitalWrite(2, HIGH, 1);
octofet.digitalWrite(3, HIGH, 1);
//octofet.digitalWrite(valve1,HIGH,1);
//octofet.digitalWrite(valve2,HIGH,2);
//octofet.digitalWrite(valve3,HIGH);
//octofet.digitalWrite(valve4,HIGH);
//octofet.digitalWrite(valve5,HIGH);
//octofet.digitalWrite(valve6,HIGH);
//octofet.digitalWrite(valve7,HIGH);
//octofet.digitalWrite(valve8,HIGH);


//octofet1.digitalWrite(valve1,HIGH);
//octofet1.digitalWrite(valve2,HIGH);
//octofet1.digitalWrite(valve3,HIGH);
//octofet1.digitalWrite(valve4,HIGH);
//octofet1.digitalWrite(valve5,HIGH);
//octofet1.digitalWrite(valve6,HIGH);
//octofet1.digitalWrite(valve7,HIGH);
//octofet1.digitalWrite(valve8,HIGH);

}
