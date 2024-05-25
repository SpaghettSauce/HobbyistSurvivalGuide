#pragma once
#include <Arduino.h>
#include <Servo.h>
int angleMove(int potentPIN);
void damageControl(int &lives, int PHS, int BUZZER);
void lifeSystem( int &lives, int lifePIN1, int lifePIN2, int lifePIN3);