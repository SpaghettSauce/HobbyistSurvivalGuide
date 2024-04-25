#define POT1 A4
#define POT2 A5

#define BUT1 7
#define BUT2 8

#define LEDB1 9
#define LEDB2 10
#define LEDP1 11
#define LEDP2 12

boolean butup1 = true;
boolean butdown1 = false;

boolean butup2 = true;
boolean butdown2 = false;


void setup() {
  pinMode(BUT1,INPUT_PULLUP);
  pinMode(BUT2,INPUT_PULLUP);

  pinMode(POT1,INPUT);
  pinMode(POT2,INPUT);

  pinMode(LEDB1, OUTPUT);
  pinMode(LEDB2, OUTPUT);
  pinMode(LEDP1, OUTPUT);
  pinMode(LEDP2, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int rot1,rot2,brt1,brt2;

  boolean butisup1 = digitalRead(BUT1);

  if (butup1 && !butisup1)
  {
    delay(10);
    butisup1 = digitalRead(BUT1);
    if (!butisup1)
    {
      butdown1 = !butdown1;
      digitalWrite(LEDB1, butdown1);
    }
  }
  butup1 = butisup1;

  boolean butisup2 = digitalRead(BUT2);

  if (butup2 && !butisup2)
  {
    delay(10);
    butisup2 = digitalRead(BUT2);
    if (!butisup2)
    {
      butdown2 = !butdown2;
      digitalWrite(LEDB2, butdown2);
    }
  }
  butup2 = butisup2;

  rot1 = analogRead(POT1);
  rot2 = analogRead(POT2);
  brt1 = rot1 / 4;
  brt2 = rot2 / 4;
  analogWrite(LEDP1,brt1);
  analogWrite(LEDP2,brt2);


}
