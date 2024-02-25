#define USE_MICRO_WIRE
#include <microWire.h>

#include "VB_MPU9250.h"
#include "VB_BMP280.h"
#include "mString.h"
#include "sdCard.h"


#include <Servo.h>


//подключенные устройства и датчики
Servo servo; //сервик
VB_BMP280 barometer; //барометр (давление)
VB_MPU9250 imu; //акселерометр (ускорение)

//делитель напряжения
const int V_R1 = 20000;
const int V_R2 = 10000;
const float DIODE_DROP = 0.2f;


//пины
const byte VoltagePin = A2; //считывание напряжения
const byte SetPin = 7; 
const byte TestButtonPin = A3; 
const byte SD_CS_Pin = 4; //sd карта
const byte ServoPin = 9; // сервик
const byte PhotoPin = A0; // фоторезистор

//номер команды
const char* TeamID = "39";

//ускорение ракеты при старте
const float StartAccel = 4;

//высота срабатывания системы спасения
const float RescueHeight = 2;

//период обновления дисплея в мс
const int update_period = 500;

//порог фоторезитора
const int PhotoTreshold = 20;

//порог разности ускорений
const float AccTreshold = 0.01;

//переменные состояния
bool startPoint = false;
bool apogeePoint = false;
bool activatePoint = false;
bool parachutePoint = false;
bool landPoint = false;


//рабочие переменные 
float voltage = 0;
float max_altitude = 0;
float start_altitude = 0;
uint32_t  last_update = 0;
float last_a = 0;
bool sdOk = false;
bool rescue_test = false;


void setup() {
  Wire.begin(); //запуск I2C
  Serial.begin(9600);
  //Serial1.begin(9600);
  
  imu.begin();
  barometer.begin();

  barometer.read();
  

  start_altitude = barometer.alti;

  pinMode(VoltagePin,INPUT);
  pinMode(TestButtonPin,INPUT);

  pinMode(SetPin,OUTPUT);
  digitalWrite(SetPin,HIGH);

  servo.attach(ServoPin);
  servo.write(0);
   
  sdOk = SD::begin(SD_CS_Pin);
}



void rescue()
{
  servo.write(65);
}

void rescueReset()
{
  servo.write(0);
}

void loop() {
  //опрос датчиков
  barometer.read();
  imu.read();
  //подсчет напряжения
  voltage = analogRead(VoltagePin) * 5.f / 1023  * ((float)(V_R1+V_R2) / (float)V_R2) + DIODE_DROP;
  float altitude = barometer.alti - start_altitude;

  float a = sqrt(imu.ax*imu.ax + imu.ay * imu.ay + imu.az * imu.az);// * G;

  if(altitude > max_altitude) //если текущая высота больше максимальной
  {
    max_altitude = altitude;
  }

  //проверка старта
  if(!startPoint && a > StartAccel){
    startPoint = true;
    max_altitude = altitude;
  }
  
  //проверка апогея
  if(startPoint && altitude + RescueHeight < max_altitude){
    apogeePoint = true;
    activatePoint = true;
    rescue();
  }

  //дисплей будем обновлять пока ракета на земле
 if ((!startPoint || landPoint) && millis() - last_update >= update_period) {  // ищем разницу
    last_update = millis();                   // сброс таймера
  }

  //тестовое срабатывание
  if(!startPoint && !rescue_test && digitalRead(TestButtonPin))
  {
    rescue_test = true;
    rescue();
  }

  if(rescue_test && !digitalRead(TestButtonPin))
  {
    rescue_test = false;
    rescueReset();
  }

  //проверка парашюта
  if(!parachutePoint && activatePoint && analogRead(PhotoPin) < PhotoTreshold)
  {
    parachutePoint = true;
  }

  //проверка приземления
  if(!landPoint && apogeePoint && abs(a - last_a) < AccTreshold)
  {
    landPoint = true;
  }


  //формирование строки телеметрии
  mString<50> message;
  message += TeamID;
  message += ';';
  message +=  millis();
  message += ';';
  message +=  voltage;
  message += ';';
  message +=  altitude;
  message += ';';
  message += a;
  message += ';';
  message += startPoint; 
  message += ';';
  message += apogeePoint; 
  message += ';';
  message += activatePoint; 
  message += ';';
  message += parachutePoint; 
  message += ';';
  message += landPoint; 
  message += ';';
  message += '\n';
  


  
  Serial.print(message.buf);
  //Serial1.print(message.buf);
  SD::print(message.buf);

  delay(20);
}
