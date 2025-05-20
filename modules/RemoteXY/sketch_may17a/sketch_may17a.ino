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

#include <WiFi.h>

// настройки соединения 
#define REMOTEXY_WIFI_SSID "LT"
#define REMOTEXY_WIFI_PASSWORD ""
#define REMOTEXY_SERVER_PORT 6377
#define REMOTEXY_ACCESS_PASSWORD "12345678"


#include <RemoteXY.h>

// конфигурация интерфейса RemoteXY  
#pragma pack(push, 1)  
uint8_t RemoteXY_CONF[] =   // 47 bytes
  { 255,1,0,0,0,40,0,19,0,0,0,76,84,0,8,1,106,200,1,1,
  2,0,4,43,87,17,107,0,16,26,129,26,54,50,12,64,16,76,105,103,
  104,116,84,101,115,116,0 };
  
// структура определяет все переменные и события вашего интерфейса управления 
struct {

    // input variables
  int8_t slider_01; // oт 0 до 100

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0

} RemoteXY;   
#pragma pack(pop)
 
/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////



void setup() 
{
  RemoteXY_Init (); 
  pinMode(7,OUTPUT);
  
}

void loop() 
{ 
  RemoteXY_Handler ();

  int light = map(RemoteXY.slider_01, 0, 100, 0, 255);
  digitalWrite(7,light);
  
  // TODO you loop code
  // используйте структуру RemoteXY для передачи данных
  // не используйте функцию delay(), вместо нее используйте RemoteXY_delay() 


}