#include "function.h"

int angleMove(int potentPIN)
{
    int val = analogRead(potentPIN);
    int angle = map(val, 0, 1024, 0, 180);
    return angle;
};

void damageControl(int lives, int photoPIN, int currentTime, int startingTime)
{
    int light = digitalRead(photoPIN);
    if (light >= 1000 && currentTime == 500)
        lives -= 1;
    unsigned long presentTime = millis();
    unsigned long timepassed = presentTime - startingTime;
}

void lifeSystem(int N, int pins[], int lives)
{
    int *arr = new int[N];
    for (int i = 0; i < N; i++)
    {
        arr[i] = i + 1 <= lives ? 1 : 0;
    }
    for (int i = 0; i < N; i++)
    {
        digitalWrite(pins[i], arr[i]);
    }
    /*
    if (lives == 3)
    {
    digitalWrite(lifePIN1,HIGH);
    digitalWrite(lifePIN2,HIGH);
    digitalWrite(lifePIN3,HIGH);
    }
    else if (lives == 2)
    {
    digitalWrite(lifePIN1,LOW);
    digitalWrite(lifePIN2,HIGH);
    digitalWrite(lifePIN3,HIGH);
    }
    else if (lives == 1)
    {
    digitalWrite(lifePIN1,LOW);
    digitalWrite(lifePIN2,LOW);
    digitalWrite(lifePIN3,HIGH);
    }
    else
    {
    digitalWrite(lifePIN1,LOW);
    digitalWrite(lifePIN2,LOW);
    digitalWrite(lifePIN3,LOW);
    }*/
}