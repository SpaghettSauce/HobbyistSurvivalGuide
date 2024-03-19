#pragma once
#include <Arduino.h>
#include <Servo.h>
int angleMove(int potentPIN);
void damageControl(int &lives, int PHS, int currentTime, int startingTime, int BUZZER);
void lifeSystem(int N, int pins[], int &lives/* int &lives, int lifePIN1, int lifePIN2, int lifePIN3*/);