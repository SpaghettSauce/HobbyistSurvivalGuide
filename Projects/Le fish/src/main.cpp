
#include <SoftwareSerial.h>
#include "RedMP3.h"
#include <Arduino.h>

#define MP3_RX 4//RX of Serial MP3 module connect to D4 of Arduino
#define MP3_TX 2//TX to D2, note that D2 can not be used as RX on Mega2560, you should modify this if you donot use Arduino UNO
MP3 mp3(MP3_RX, MP3_TX);

int8_t index  = 0x01;//the first song in the TF card
int8_t volume = 0x1d;//0~0x1e (30 adjustable level)

const int buttonPin1 = 12;
const int buttonPin2 = 13;

void setup()
{
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  delay(500);
}

void loop()
{
  int buttonState1 = digitalRead(buttonPin1);
  int buttonState2 = digitalRead(buttonPin2);

   if (buttonState1 == LOW) { 
    int8_t index  = 0x01;
    mp3.playWithVolume(index,volume);
    delay(50);
  }

  if (buttonState2 == LOW) { 
    int8_t index  = 0x02;
    mp3.playWithVolume(index,volume);
    delay(50);
  }
}
