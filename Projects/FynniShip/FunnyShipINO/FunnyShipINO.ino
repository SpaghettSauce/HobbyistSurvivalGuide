#include <Octofet.h>
#include <SPI.h>
#include <Wire.h>
#include <L3G.h>

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

constexpr auto pinCS1 = 6;
constexpr auto pinCS2 = 7;
L3G gyro;
Octofet octofet(pinCS);

void setup() {
  octofet.begin();

  pinMode(valve,OUTPUT);

  pinMode(pump1_1, OUTPUT);
  pinMode(pump1_2,OUTPUT);

  pinMode(pump2_1, OUTPUT);
  pinMode(pump2_2,OUTPUT);

  pinMode(pump3_1, OUTPUT);
  pinMode(pump3_2,OUTPUT);

  pinMode(pump4_1, OUTPUT);
  pinMode(pump4_2,OUTPUT);
  Serial.begin(9600);
  Wire.begin();

  if (!gyro.init())//Проверка подключения гироскопа к ардуино 
  {
    Serial.println("Failed to autodetect gyro type!");
    while (1);
  }

  gyro.enableDefault();
}

void loop() {
  
  gyro.read();

  if (map((int)gyro.g.x,-80 , 40 , 0 , 10 ) >=  100)
  {
    octofet.digitalWrite(valve1,HIGH);
    analogWrite(pump1_1, 255);
    analogWrite(pump1_2,0);
    delay (500);

    analogWrite(pump1_1, 0);
    analogWrite(pump1_2,255);
    
    octofet.digitalWrite(valve1,LOW);
    octofet.digitalWrite(valve2,HIGH);
  }

 if (map((int)gyro.g.x,-80 , 40 , 0 , 10 ) <=  100)
  {
    octofet.digitalWrite(valve3,HIGH);
    analogWrite(pump2_1, 255);
    analogWrite(pump2_2,0);
    delay (500);

    analogWrite(pump2_1, 0);
    analogWrite(pump2_2,255);
    
    octofet.digitalWrite(valve3,LOW);
    octofet.digitalWrite(valve4,HIGH);
  }
   if (map((int)gyro.g.x,-80 , 40 , 0 , 10 ) >=  50)
  {
    octofet.digitalWrite(valve5,HIGH);
    analogWrite(pump3_1, 255);
    analogWrite(pump3_2,0);
    delay (500);

    analogWrite(pump3_1, 0);
    analogWrite(pump3_2,255);
    
    octofet.digitalWrite(valve5,LOW);
    octofet.digitalWrite(valve6,HIGH);
  }
   if (map((int)gyro.g.x,-80 , 40 , 0 , 10 ) <=  50)
  {
    octofet.digitalWrite(valve7,HIGH);
    analogWrite(pump4_1, 255);
    analogWrite(pump4_2,0);
    delay (500);

    analogWrite(pump4_1, 0);
    analogWrite(pump4_2,255);
    
    octofet.digitalWrite(valve7,LOW);
    octofet.digitalWrite(valve8,HIGH);
  }

  Serial.print("G ");
  Serial.print("X: ");
  Serial.print(map((int)gyro.g.x,-500 , 500 , 0 , 100 )); 
  Serial.print(" Y: ");
  Serial.print(map((int)gyro.g.y,-500 , 500 , 0 , 100 ));      
  Serial.print(" Z: ");
  Serial.println(map((int)gyro.g.z,-500 , 500 , 0 , 100 )); 

  delay(100);
}
