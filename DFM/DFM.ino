#include <SPI.h>            
#include <Adafruit_GFX.h>  
#include <TFT_ILI9163C.h>   

#define	BLACK   0x0000
#define	RED     0xF800  
#define	GREEN   0x07E0
#define LIME    0x07FF
#define YELLOW  0xFFE0
#define ORANGE 0xFA60  

#define PIN_TRIG 7
#define PIN_ECHO 5

long duration, cm;

#define __CS 10
#define __CS2 6
#define __CS3 3
#define __DC 9
#define __RES 8
#define __RES2 4
#define __RES3 2

int x = 1;

TFT_ILI9163C display = TFT_ILI9163C(__CS, __DC, __RES);
TFT_ILI9163C display2 = TFT_ILI9163C(__CS2, __DC, __RES2);
TFT_ILI9163C display3 = TFT_ILI9163C(__CS3, __DC, __RES3); 


void setup() {
  display.begin(); 
  display2.begin();
  display3.begin();
  Serial.begin(9600);
  display.setRotation(4);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
}

void loop() 
{
  cm = len(PIN_TRIG,PIN_ECHO);
  Serial.println(cm);

    REC1(display,cm* 5, RED) ;
  if (cm > 20 )
  {
    REC1(display2, cm * 2, YELLOW );
    if (cm >30)
    {
      REC1(display3,cm,GREEN);
    }
  }


}

int len (int TRIG,int ECHO)
{
digitalWrite(TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIG, HIGH);

  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH);

  cm = (duration / 2) / 19.1;
  delay(50);
  return cm;
}

void REC1(TFT_ILI9163C displac, int width, int colour )
{
  
  displac.fillRect(0, 0, width, 144, colour);
  display.fillRect(width, 0, 25, 144, BLACK);

}
