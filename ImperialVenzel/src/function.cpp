#include "function.h"

int angleMove(int potentPIN){
    int val = analogRead(potentPIN);
    int angle = int(val/1024.0 * 270.0); 
    angle = constrain(angle,0,180);
    return angle;
}

void damageControl(int lives,int photoPIN, int currentTime, int startingTime){
    int light = digitalRead(photoPIN);
    if ( light >= 1000 && currentTime == 500 )  
    lives -=1;
    unsigned long presentTime = millis();
    unsigned long  timepassed= presentTime - startingTime;

}

void lifeSystem(int lifePIN1,int lifePIN2,int lifePIN3, int lives)
{
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
    }
}