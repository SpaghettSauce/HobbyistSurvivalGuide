#pragma once
#include <Arduino.h>
#include <Servo.h>
int angleMove(int potentPIN);
void damageControl(int lives, int photoPIN, int currentTime, int startingTime);
void lifeSystem(int N, int pins[], int lives);