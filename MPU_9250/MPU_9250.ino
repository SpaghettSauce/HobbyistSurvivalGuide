#include <LiquidCrystal_I2C.h>    //скачать, нужно для экранчика с шиной i2c
#include <MPU9250.h>              //надо скачивать, основная библиотека для работы с сенсором
#include <Wire.h>                 //уже есть, библиотека для работы с шинаи I2C
 
LiquidCrystal_I2C lcd(0x27, 16, 2); // задание параметров дисплея
                                    //адрес I2C-конвертера 0х27 или 0х3f
 
MPU9250 mpu;                      // Объявляем переменную для датчика
 
void setup()
{
  Serial.begin(115200);           //Запускаем монитор порта
  Wire.begin();                   //Запускаем работу с шиной I2C
  delay(2000);
  mpu.setup(0x68);                   //Адрес датчика на шине I2C
  mpu.setMagneticDeclination(7.4);  //в скобках необходимо указать магнинтное отклонение
  delay(5000);
 
//Калибровка датчика. Запускаем монитор по последовательному соединению 
//и следуем инструкции
  Serial.println("Accel Gyro calibration will start in 5sec.");               
  Serial.println("Please leave the device still on the flat plane.");         
  mpu.verbose(true);
  delay(5000);
  mpu.calibrateAccelGyro();
 
  Serial.println("Mag calibration will start in 5sec.");
  Serial.println("Please Wave device in a figure eight until done.");
  delay(5000);
  mpu.calibrateMag();
 
  print_calibration();
  mpu.verbose(false);
 
  //экран
  lcd.init();                        // запуск дисплея
  lcd.backlight();                   // включение подсветки дисплея
  lcd.setCursor(0, 0);               // установка курсора в ячейку на дисплее
  lcd.print("x");                    // вывод на экран
  lcd.setCursor(6, 0);
  lcd.print("y");
  lcd.setCursor(11, 0);
  lcd.print("z");
  lcd.setCursor(0, 1);
  lcd.print("ax:");
  lcd.setCursor(8, 1);
  lcd.print("ay:");
}
 
void loop()
{
  static uint32_t prev_ms = millis();
  if ((millis() - prev_ms) > 100)
  {
    mpu.update();
 
    prev_ms = millis();
 
    lcd.setCursor(1, 0);
// выводим на экран округленное значение по оси X
    lcd.print(int(mpu.getRoll()));       
    lcd.print(" ");
    lcd.setCursor(7, 0);
// выводим на экран округленное значение по оси Y
    lcd.print(int(mpu.getPitch()));      
    lcd.print(" ");
    lcd.setCursor(12, 0);
// выводим на экран округленное значение по оси Z
    lcd.print(int(mpu.getYaw()));        
    lcd.print(" ");
    lcd.setCursor(3, 1);
 
// задаем переменную для ускорения по оси X
// выводим на экран округленное значение ускорения в размерности g*1000
    float ux = mpu.getAcc(0) * 1000;     
    lcd.print(int(ux));                  
    lcd.print("  ");
 
// задаем переменную для ускорения по оси Y
// выводим на экран округленное значение ускорение в размерности g*1000
    lcd.setCursor(11, 1);
    float uy = mpu.getAcc(1) * 1000;     
    lcd.print(int(uy));                  
    lcd.print("  ");
    delay(50);
 
  }
}
 
void print_calibration() { //функция выводящая откалибрированнае данные на экран
  Serial.println("< calibration parameters >");
  Serial.println("accel bias [g]: ");
  Serial.print(mpu.getAccBiasX() * 1000.f / (float)MPU9250::CALIB_ACCEL_SENSITIVITY);
  Serial.print(", ");
  Serial.print(mpu.getAccBiasY() * 1000.f / (float)MPU9250::CALIB_ACCEL_SENSITIVITY);
  Serial.print(", ");
  Serial.print(mpu.getAccBiasZ() * 1000.f / (float)MPU9250::CALIB_ACCEL_SENSITIVITY);
  Serial.println();
  Serial.println("gyro bias [deg/s]: ");
  Serial.print(mpu.getGyroBiasX() / (float)MPU9250::CALIB_GYRO_SENSITIVITY);
  Serial.print(", ");
  Serial.print(mpu.getGyroBiasY() / (float)MPU9250::CALIB_GYRO_SENSITIVITY);
  Serial.print(", ");
  Serial.print(mpu.getGyroBiasZ() / (float)MPU9250::CALIB_GYRO_SENSITIVITY);
  Serial.println();
  Serial.println("mag bias [mG]: ");
  Serial.print(mpu.getMagBiasX());
  Serial.print(", ");
  Serial.print(mpu.getMagBiasY());
  Serial.print(", ");
  Serial.print(mpu.getMagBiasZ());
  Serial.println();
  Serial.println("mag scale []: ");
  Serial.print(mpu.getMagScaleX());
  Serial.print(", ");
  Serial.print(mpu.getMagScaleY());
  Serial.print(", ");
  Serial.print(mpu.getMagScaleZ());
  Serial.println();
}