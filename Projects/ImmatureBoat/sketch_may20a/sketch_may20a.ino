/*
   -- New project --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 3.1.13 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.15.01 or later version;
     - for iOS 1.12.1 or later version;
    
   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.    
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// можете включить вывод отладочной информации в Serial на 115200
//#define REMOTEXY__DEBUGLOG    

// определение режима соединения и подключение библиотеки RemoteXY 
#define REMOTEXY_MODE__WIFI_POINT
#define REMOTEXY__DEBUGLOG    

#include <ESP8266WiFi.h>
#include <RemoteXY.h>
#include <Servo.h>  // Подключаем библиотеку Servo

// настройки соединения 
#define REMOTEXY_WIFI_SSID "IMboat"
#define REMOTEXY_WIFI_PASSWORD ""
#define REMOTEXY_SERVER_PORT 6377
#define REMOTEXY_ACCESS_PASSWORD "12345678"


#include <RemoteXY.h>

// конфигурация интерфейса RemoteXY  
#pragma pack(push, 1)  
uint8_t RemoteXY_CONF[] =   // 120 bytes
  { 255,2,0,4,0,113,0,19,0,0,0,73,77,98,111,97,116,0,132,2,
  106,200,200,84,1,1,5,0,4,17,45,17,64,41,19,15,46,32,2,26,
  4,53,77,52,16,128,24,59,18,160,2,26,129,5,40,37,12,34,15,28,
  9,64,17,208,156,208,190,209,130,208,190,209,128,0,129,49,64,57,9,136,
  13,40,7,64,17,208,155,208,181,208,178,208,190,92,208,146,208,191,209,128,
  208,176,208,178,208,190,0,67,5,118,40,10,8,69,76,13,78,2,26,2 };
  
// структура определяет все переменные и события вашего интерфейса управления 
struct {

    // input variables
  int8_t slider_ver; // oт -100 до 100
  int8_t slider_gor; // oт -100 до 100

    // output variables
  float value_02;

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0

} RemoteXY;   
#pragma pack(pop)
 
/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////
Servo steeringServo;

const int motorPinPWM1 = D1;
const int motorPinPWM2 = D3; // ШИМ-пины для управления скоростью мотора
const int servoPin = D2; // Пин для серводвигателя


void setup() 
{
  RemoteXY_Init (); 
  
   // Инициализация пина мотора
  pinMode(motorPinPWM1, OUTPUT);
  //pinMode(motorPinPWM2, OUTPUT);

  // Прикрепляем серву к пину
  steeringServo.attach(servoPin);
  Serial.begin(115200);
}

void loop() 
{ 
  RemoteXY_Handler ();
  if(RemoteXY.connect_flag == false) //Если не присоеденился телефон
 {
  analogWrite(motorPinPWM1, 0); //выключаем мотор
  analogWrite(motorPinPWM2, 0);
 }
 else{ //если подсоеденился телеофн
 
    // Управление мотором: преобразование -100 до 100 в -255 до 255
  int motorSpeed = map(RemoteXY.slider_ver, -100, 100, -255, 255);
  if (motorSpeed > 0){ //если скорость положительная, то крутим по часовой стрелке
     analogWrite(motorPinPWM1, motorSpeed);
     analogWrite(motorPinPWM2, 0);
     RemoteXY.value_02 = motorSpeed;
  }
  if (motorSpeed < 0){ //если скорость отрицательная, то крутим против часовой стрелки
    analogWrite(motorPinPWM2, -motorSpeed);
     analogWrite(motorPinPWM1, 0);
     RemoteXY.value_02 = motorSpeed;
  }

  // Управление сервой: преобразуем -100 до 100 в угол от 5 до 175 градусов
  int angle = map(RemoteXY.slider_gor, -100, 100, 5, 175);
  steeringServo.write(angle);

 }
}