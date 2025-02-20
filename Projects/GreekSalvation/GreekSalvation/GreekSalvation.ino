#define mPAN 5
#define mGOM 6

#define sPAN A0
#define sGOM A1
void setup()
{
    pinMode(mPAN,OUTPUT);
    pinMode(mGOM,OUTPUT);
    Serial.begin(9600);     
}

void loop()
{
    int vPAN;
    int vGOM;
    vPAN = analogRead(sPAN);    
    vGOM = analogRead(sGOM);   

    Serial.print("PAN:");
    Serial.println(vPAN);
    Serial.print("GOM:");
    Serial.println(vGOM);

    if (vPAN <= 300){
    digitalWrite(mPAN,HIGH);
    delay(1500);
    }
    if (vGOM <= 300){
    digitalWrite(mGOM,HIGH);
    delay(1500);
    delay(100);
    }

}

/*Dry: (520 430]
Wet: (430 350]
Water: (350 260]
*/