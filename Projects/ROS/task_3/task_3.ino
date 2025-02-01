/*Основная разница этого задания от 2, то что в 2 мы считывали значения с рос, в зависимости от них включали светодиод. Тут мы сами нажимаем на кнопки, потом отправляем эту инфу росу и потом зажигаем светодиод. 
Делается это через паблишер, который отправляет наши данные росу.*/


#include <ros.h>
#include <std_msgs/String.h>

#define LedPin 6
#define Button1Pin 9
#define Button2Pin 11

ros::NodeHandle nh; //переменная узла с рос
std_msgs::String msg; //в msg будем хранить сообщения с роса
ros::Publisher pub("/led/control", &msg); //создаёт паблишер (передатчик) в топик "/led/control".


String lightMode = "off"; //таже тема что в прошлом задании с статусами светодиода
unsigned long lastOn = 0; //и временем

void LightState() { //с 2 задания
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
  nh.advertise(pub); //регистрирует паблишер для отправки сообщений в ROS

  lightMode = "off";
}

void loop() {
  nh.spinOnce(); //обновляет соединение с ROS 
  bool button1Pressed = !digitalRead(Button1Pin); //считываем нажатие обоих кнопок
  bool button2Pressed = !digitalRead(Button2Pin);

  String newMode;
  if (button1Pressed && button2Pressed) {
    newMode = "on";
  } else if (button1Pressed) {
    newMode = "blink";
  } else {
    newMode = "off";
  }

  if (newMode != lightMode) { //если режим изменился, с off на on к примеру
    lightMode = newMode;
    msg.data = lightMode.c_str(); //конвертирует String в формат ROS.
    pub.publish(&msg); //и отправляем сообщение в /led/control
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
