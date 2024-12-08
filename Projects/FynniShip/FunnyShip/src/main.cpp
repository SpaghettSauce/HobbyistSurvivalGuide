#include <Arduino.h>

#define Motor 5 // Pin for motor control
int val = 0;    // Variable to store motor speed

void setup() {
  pinMode(Motor, OUTPUT); // Set motor pin as output
  Serial.begin(9600);     // Begin serial communication at 9600 bps
}

void loop() {
  if (Serial.available() > 0) {  // Check if data is available on Serial
    String input = Serial.readStringUntil('\n'); // Read the input as a string until newline
    val = input.toInt();  // Convert the string input to an integer
    val = constrain(val, 0, 255); // Ensure the value is between 0 and 255
    Serial.print("Setting motor speed to: ");
    Serial.println(val); // Print the motor speed for debugging
  }
  analogWrite(Motor, val); // Set motor speed
}
