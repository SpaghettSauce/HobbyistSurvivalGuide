
#include <Wire.h> // Библиотека для работы с шиной I2C
#include <SPI.h>  // Библиотека для работы с шиной SPI
#include <Adafruit_BMP280.h> // Библиотека для работы с датчиком BMP280, скачать:Adafruit.. BMP280_Library,Sensor-master,BusIO

// Для подключения по шине I2C
//Adafruit_BMP280 bmp;

// Для подключения по аппаратному SPI (указываем только номер пина CS)
//#define PIN_CS 10
//Adafruit_BMP280 bmp(PIN_CS);

// Для подключения по программному SPI (указываем все пины интерфейса)
#define PIN_SCK  13
#define PIN_MISO 12
#define PIN_MOSI 11
#define PIN_CS   10
Adafruit_BMP280 bmp(PIN_CS, PIN_MOSI, PIN_MISO,  PIN_SCK);//инициализируем сенсор, указывая пины)

void setup() {
  Serial.begin(9600); // Для вывода отладочной информации в терминал
    if(!bmp.begin()) { // проверяем если датчик BMP280 не найден
    Serial.println("BMP280 SENSOR ERROR"); // Выводим сообщение об ошибке
    while(1); // Переходим в бесконечный цикл
  }
//функция снизу нужна для настройки сенсора, чтобы настраивать вместо переменных пишите цифры
bmp.setSampling(Adafruit_BMP280::MODE_NORMAL, // Режим работы
                Adafruit_BMP280::SAMPLING_X2, // Точность изм. температуры
                Adafruit_BMP280::SAMPLING_X16, // Точность изм. давления
                Adafruit_BMP280::FILTER_X16, // Уровень фильтрации
                Adafruit_BMP280::STANDBY_MS_500); // Период просыпания, мСек

}
void loop() {
  // Выводим значение температуры
  Serial.print(F("Temperature = "));
  Serial.print(bmp.readTemperature()); // Функция измерения температуры
  Serial.println(" *C");

  // Выводим значение атмосферного давления
  Serial.print(F("Pressure = "));
  Serial.print(bmp.readPressure());  // Функция измерения атм. давления
  Serial.println(" Pa");

  // Выводим значение высоты
  Serial.print(F("Approx altitude = "));
  Serial.print(bmp.readAltitude(1013.25)); // Функция измерения высоты
  Serial.println(" m");
}