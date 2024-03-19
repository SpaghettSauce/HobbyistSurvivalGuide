#include "function.h"

int angleMove(int potentPIN)
{
    int val = analogRead(potentPIN);
    int angle = map(val, 0, 1024, 0, 180);
    Serial.println(angle);
    return angle;
};

void damageControl(int &lives, int PHS, int currentTime, int startingTime, int BUZZER)
{
    int light = analogRead(PHS);
    //Serial.println(light);
    if (light <= 100 /*&& currentTime == 500*/)
    {
        lives -= 1;
        tone (BUZZER,900,200);
    }
        /*unsigned long presentTime = millis();
        currentTime = presentTime - startingTime;*/
}

void lifeSystem(int N, int pins[], int &lives/*,int &lives, int lifePIN1, int lifePIN2, int lifePIN3*/)
{//умный крутой способ (с)Rubailo Intellectual Property 
    int *arr = new int[N];
    for (int i = 0; i < N; i++)
    {
        arr[i] = i + 1 <= lives ? 1 : 0;
    }
    for (int i = 0; i < N; i++)
    {
        digitalWrite(pins[i], arr[i]);
    }
    /* тривиальный способ
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