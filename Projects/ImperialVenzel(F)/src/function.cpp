#include "function.h"

int angleMove(int potentPIN)//система движения сервика
{
    int val = analogRead(potentPIN); //считываем значение с потенциометра
    int angle = map(val, 0, 1024, 0, 180); //приводим его к нормальным цифрам 
    return angle;//возвращаем
};

void damageControl(int &lives, int PHS, int BUZZER) //система урона
{
 //считываем значение с фоторезистора
 //если они >1000 (посвети на него лазером чтобы узнать какое значение нужно)
 //то жизни -1
 //пропиликай пищалкой   
        
}
void lifeSystem(int &lives, int lifePIN1, int lifePIN2, int lifePIN3) //система жизней
{
    if (lives == 3)//если жизни 3
    {
    digitalWrite(lifePIN1,HIGH);//включи все три светодиода
    digitalWrite(lifePIN2,HIGH);
    digitalWrite(lifePIN3,HIGH);
    }
    else if ... //и так далее

}