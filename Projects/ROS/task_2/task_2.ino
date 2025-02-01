/* Грубо говоря что тут происходит: 
Подключаемся к ROS и подписываемся на топик "led/control"
От этого топика рос получает команды и отправляет нам:
"on" → Включает светодиод
"off" → Выключает светодиод
"blink" → Светодиод мигает с задержкой 
В loop() проверяем, нужно ли мигать, и управляет светодиодом
Постоянно обрабатывает сообщения ROS через nh.spinOnce().*/

#include <ros.h> //сам рос
#include <std_msgs/String.h> //библиотека для работы с string

#define LedPin 6

ros::NodeHandle nh; // создаем объект NodeHandle, который дальше будет называться nh, он нам нужен для взаимодействия с рос
String lightMode = "blink";  //в переменной lightmode будем хранить статус нашего светодиода, у нее вообще будут значения on,off,blink, изначально ставим blink
unsigned long lastOn = 0; // переменная, хранящая время последнего переключения светодиода, по заданию нужно хранить

void ledCallback(const std_msgs::String& msg) {  //первая функция ledCallback, она используется для обработки сообщений которые мы получаем от роса, буквально на вход получаем строку от роса
  String command = msg.data.c_str(); //а тут преобразовываем ее в нормальную строку

  if (command == "on") { //если пришла от роса команда on
    lightMode = "on";
    digitalWrite(LedPin, HIGH); //то включаем 
  } else if (command == "off") { // и так далее
    lightMode = "off";
    digitalWrite(LedPin, LOW);
  } else if (command == "blink") {
    lightMode = "blink"; //мигаем
  }
}

ros::Subscriber<std_msgs::String> sub("led/control", &ledCallback); //создаётся подписчик на топик "led/control", который вызывает ledCallback, когда приходит сообщение

void setup() {
  pinMode(LedPin, OUTPUT);
  nh.initNode(); //создаем узел рос
  nh.subscribe(sub); //создаем подписчика

  lightMode = "blink";
}

void loop() {
  nh.spinOnce(); //обновляет связь с ROS, проверяет входящие сообщения

  if (lightMode == "blink") {
    unsigned long now = millis();
    if (now - lastOn >= 4000 && digitalRead(LedPin) == LOW) {//если светодиод выключен и прошло ≥ 4 секунд, он включается, а lastOn обновляется
      digitalWrite(LedPin, HIGH);
      lastOn = now;
    } else if (now - lastOn >= 2000 && digitalRead(LedPin) == HIGH) {
      digitalWrite(LedPin, LOW);
      lastOn = now;
    }
  }