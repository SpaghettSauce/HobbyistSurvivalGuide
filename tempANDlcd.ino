#include <LiquidCrystal.h>
#define DIODE_DROP 0.7
LiquidCrystal lcd(13,12,11,10,9,8);
const int thermistorPin = A1;

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);

}

void loop() {
  
  float sensorValue = analogRead(thermistorPin);
  float temperatureC = map(sensorValue, 0, 1023, 0, 100); 
  Serial.print("Temperature: ");
  Serial.print(temperatureC-20);
  Serial.println(" C");
  lcd.setCursor(1,0);
  lcd.print(temperatureC-20, 2);
  lcd. print ("C");
  delay(1000);

}