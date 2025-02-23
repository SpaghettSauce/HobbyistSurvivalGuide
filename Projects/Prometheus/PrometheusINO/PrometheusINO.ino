#define mPAN 5

#define mGOM1 8
#define mGOM2 7

#define sPAN A0
#define sGOM A1
void setup()
{
    pinMode(mPAN,OUTPUT);
    pinMode(mGOM1,OUTPUT);
    pinMode(mGOM2,OUTPUT);

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
    //Serial.print("GOM:");
    //Serial.println(vGOM);

    //
    //digitalWrite(mGOM1,LOW);
    //digitalWrite(mGOM2,HIGH);

    if (vPAN >= 300){
    digitalWrite(mPAN,HIGH);
    delay(1500);
    }
    if (vGOM >= 300){
    digitalWrite(mGOM1,HIGH);
    delay(1500);
    }
    else{
      digitalWrite(mGOM1, LOW);
    }

}

/*Dry: (520 430]
Wet: (430 350]
Water: (350 260]
*/