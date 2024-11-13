
#include <SoftwareSerial.h>
#include "RedMP3.h"
#include <Arduino.h>

#define fish 6
#define french 12
#define cover 13

#define MP3_RX 4//RX of Serial MP3 module connect to D4 of Arduino
#define MP3_TX 2//TX to D2, note that D2 can not be used as RX on Mega2560, you should modify this if you donot use Arduino UNO
MP3 mp3(MP3_RX, MP3_TX);

int8_t index  = 0x01;//the first song in the TF card
int8_t volume = 0x0D;//0~0x1e (30 adjustable level)


void setup()
{

  pinMode(cover, INPUT_PULLUP);
  pinMode(french, INPUT_PULLUP);
  delay(500);
}

void loop()
{
  int speed = 150;
  int buttonState1 = digitalRead(cover);
  int buttonState2 = digitalRead(french);

   if (french == LOW) { 
    analogWrite(fish,speed);

    int8_t index  = 0x01;
    mp3.playWithVolume(index,volume);
    delay(50);
  }

  if (cover == LOW) { 
    speed -= 100;
    analogWrite(fish,speed);
    int8_t index  = 0x02;
    mp3.playWithVolume(index,volume);
    delay(50);
  }
}
