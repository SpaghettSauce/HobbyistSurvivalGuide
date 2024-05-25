#include "function.h"

#define PERIOD 500
#define MAX 180.0

uint32_t time;

int angleMove(int potentPIN)
{
    int val = analogRead(potentPIN);
    /*int angle = map(val, 0, 1024, 0, 180);*/
    int angle = int(val / 1024.0 * MAX);
    angle = constrain(angle, 0 ,180);
    return angle;
}

void damageControl(int &lives, int PHS, int currentTime, int startingTime, int BUZZER)
{
    int light = analogRead(PHS);
    if (light <= 100)
    {
        if (millis() - time >= PERIOD) {  // ищем разницу
            time = millis();          
            lives -= 1;
            tone (BUZZER,900,200);
        }
    }
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
