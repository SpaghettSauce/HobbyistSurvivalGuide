#include <ros.h>
#include <std_msgs/String.h>

#define LedPin 6
#define Button1Pin 9
#define Button2Pin 11

ros::NodeHandle nh;
std_msgs::String msg;
ros::Publisher pub("/led/control", &msg);

String lightMode = "off";
unsigned long lastOn = 0;

void LightState() {
  if (lightMode == "on") {
    digitalWrite(LedPin, HIGH);
  } else if (lightMode == "off") {
    digitalWrite(LedPin, LOW);
  }
}

void setup() {
  pinMode(LedPin, OUTPUT);
  pinMode(Button1Pin, INPUT_PULLUP);
  pinMode(Button2Pin, INPUT_PULLUP);

  nh.initNode();
  nh.advertise(pub);

  lightMode = "off";
}

void loop() {
  nh.spinOnce();
  bool button1Pressed = !digitalRead(Button1Pin);
  bool button2Pressed = !digitalRead(Button2Pin);

  String newMode;
  if (button1Pressed && button2Pressed) {
    newMode = "on";
  } else if (button1Pressed) {
    newMode = "blink";
  } else {
    newMode = "off";
  }

  if (newMode != lightMode) {
    lightMode = newMode;
    msg.data = lightMode.c_str();
    pub.publish(&msg);
  }

  if (lightMode == "blink") {
    unsigned long now = millis();
    if (now - lastOn >= 4000 && digitalRead(LedPin) == LOW) {
      digitalWrite(LedPin, HIGH);
      lastOn = now;
    } else if (now - lastOn >= 2000 && digitalRead(LedPin) == HIGH) {
      digitalWrite(LedPin, LOW);
      lastOn = now;
    }
  } else {
    LightState();
  }
}
