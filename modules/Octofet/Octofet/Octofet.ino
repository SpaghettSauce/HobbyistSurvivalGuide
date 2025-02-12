// Two Octofet libraries have to be included first
#include <Octofet.h>
#include <SPI.h>

// any GPIO pin can be used as pinCS
constexpr auto pinCS = 10;

// Create an object of Octofet type to use hardware SPI
Octofet octofet(pinCS);

void setup() {
    // Start communication with the board 
    octofet.begin();
}

void loop() {
    // Set each power switch to "on" state
    // one by one with 1 second interval
    for (int i = 0; i < 8; i++) {
        octofet.digitalWrite(i, HIGH);
        delay(1000);
    }
    // Similarly, set switches to "off" state
    for (int i = 0; i < 8; i++) {
        octofet.digitalWrite(i, LOW);
        delay(1000);
    }
}