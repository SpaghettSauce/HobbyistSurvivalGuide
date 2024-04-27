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
    REC1(cm * 5);
  if (cm > 20 )
  {
    REC2(cm * 2 );
    if (cm >30)
    {
      REC3(cm);
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

void REC1(int width)
{

  display.fillRect(0, 0, width, 144, RED);
  //display.fillRect(width, 0, 10, 144, RED);
  //display.fillRect(width, 0, 10, 144, BLACK);
  display.fillScreen(BLACK);
}
void REC2(int width)
{

  display2.fillRect(0, 0, width, 144, YELLOW);
  display2.fillScreen(BLACK);
   display2.fillScreen(BLACK);
  //display2.fillRect(width, 0, 10, 144, YELLOW);
  //display2.fillRect(width, 0, 10, 144, BLACK);
}
void REC3(int width)
{

  display3.fillRect(0, 0, width, 144, GREEN);
  display3.fillScreen(BLACK);
  //display3.fillRect(width, 0, 10, 144, GREEN);
  //display3.fillRect(width, 0, 10, 144, BLACK);
}