/*
  Оригинальный код от Batoni: https://github.com/NobodyButAny/GyroPID.git
*/

#include <Wire.h>
#include "MPU6050.h"
#include "GyverRelay.h"
#include <Octofet.h>

#define HysteresisRelay GyverRelay // Более логичное название :P

// Пины насосов + клапаны
#define pump1_1 11
#define pump1_2 10

#define pump2_1 9
#define pump2_2 8

#define pump3_1 7 
#define pump3_2 6

#define pump4_1 4
#define pump4_2 3

float const alpha = 0.9;   //Параметр фильтра
constexpr auto pinCS = 5; //Пин октофета
constexpr auto deviceCount = 2;

// Калибровочные параметры
// -600.00000,     1337.00000,     1046.00000,     -109.00000,     63.00000,       9.00000
MPU6050 gyroAccel;

/*
  Контроллеры для управления инертным обьектом с релейным управлением типа помпы

  Значение угла нельзя однозначно перевести в сигнал ВКЛ/ВЫКЛ для движущегося обьекта -
  необходимо также учитывать темп изменения значения и иметь приемлемый диапазон,
  чтобы избегать избыточных контролирующих сигналов и (лишних) осцилляций

  Вход: состояние датчика (или производный от него параметр)

  Выход: 0 / 1 - управляющий сигнал для реле ( очевидно связанного с параметром :P )
    xController.getResult()

  !!! ТРЕБУЕТ НАСТРОЙКУ  (см. setup) !!!
*/
HysteresisRelay rollController(NORMAL); // REVERSE меняет ВКЛ и ВЫКЛ местами
HysteresisRelay pitchController(NORMAL);


Octofet octofet(pinCS,deviceCount);//инициализация правого* октофета
//Octofet octofet(pinCS2);//инициализация правого* октофета

float roll, pitch; // углы
float prevTime;

// Калибровка MPU
// Загрузим калибровочные параметры в датчик, у MPU нет памяти (в отличии от L3G...)
void setOffsets()
{
  gyroAccel.setXAccelOffset(-600);
  gyroAccel.setYAccelOffset(1337);
  gyroAccel.setZAccelOffset(1046);
  gyroAccel.setXGyroOffset(-109);
  gyroAccel.setYGyroOffset(63);
  gyroAccel.setZGyroOffset(9);
}

void setup()
{
  Serial.begin(9600);
  octofet.begin();
 // octofet1.begin();

  pinMode(pump1_1, OUTPUT);
  pinMode(pump1_2,OUTPUT);

  pinMode(pump2_1, OUTPUT);
  pinMode(pump2_2,OUTPUT);

  pinMode(pump3_1, OUTPUT);
  pinMode(pump3_2,OUTPUT);

  pinMode(pump4_1, OUTPUT);
  pinMode(pump4_2,OUTPUT);
  Serial.begin(9600);

  Wire.begin(); // I2C
  Serial.println("Arduino not dead!");

  gyroAccel.initialize(ACCEL_FS::A2G, GYRO_FS::G250DPS);
  while (!gyroAccel.testConnection())
  {
    Serial.println("Failed to connect to the gyroscope!");
    gyroAccel.initialize();
    delay(250);
  }

  setOffsets(); // Загрузим калибровочные пааметры

  // !ВНИМАНИЕ!
  // Значения ниже подобраны наугад - проверить с кораблём и поменять в случае чего

  // Целевое значение - просто установить желаемый уровень
  rollController.setpoint = 0.0;
  // Гистерезис - приемлемая ошибка (перелёт-недолёт, читать как 0 +- 1 градус)
  // Увеличивать для стабилизации, если точность удержания невозможно держать в узком окне
  // Уменьшать, если управление достаточно отзывчиво, а удержание не требует постоянной подстройки
  rollController.hysteresis = 1.0;
  // Коэффициент учёта скорости изменения - позволяет прогнозировать состояние системы во времени и заранее отключать контроль
  // Диапазон: 0-100, предположу что больше 2 будет необходимо
  rollController.k = 0.4;

  // ... настроить pitchController также (значения другие - суть та же)

  // Настроим пины для реле/насосов
  //pinMode(FRONT_RIGHT, OUTPUT);
  //pinMode(FRONT_LEFT, OUTPUT);
  //pinMode(REAR_RIGHT, OUTPUT);
  //pinMode(REAR_LEFT, OUTPUT);
}

void loop()
{
  // Тут чистые ненормированные значения с датчика
  int16_t ax, ay, az, gx, gy, gz;

  // Передаём ссылки на переменные ускорений (спроси Даню для разьяснений)
  gyroAccel.getAcceleration(&ax, &ay, &az);

  // Нормируем исходя из предельных значений (16384 в внутренних единицах - предел 2G)
  float accelX = ax / 16384.0;
  float accelY = ay / 16384.0;
  float accelZ = az / 16384.0;

  // считаем углы исходя из геометрических соображений :)
  float accelRoll = atan2(accelY, accelZ) * 180.0 / PI;
  float accelPitch = atan2(-accelX, sqrt(accelY * accelY + accelZ * accelZ)) * 180.0 / PI;

  // проделываем то же с гироскопом (но гироскоп даёт нам угловые скорости вместо проекций ускорений)
  // угол из него просто не получить
  gyroAccel.getRotation(&gx, &gy, &gz); 
  float gyroRollRate = gx / 131.0;
  float gyroPitchRate = gy / 131.0;

  // время между замерами гироскопа важно измерять для интегрирования скоростей в углы
  unsigned long currentTime = millis();
  float dt = (currentTime - prevTime) / 1000.0;
  prevTime = currentTime;



  // Применим комплементарный фильтр
  // подмешаем в замер интегрированных показаний гироскопа замер акселерометра
  // притом alpha (< 1) подавляет дрифт гироскопа (без него был бы вечный рос из-за шума)
  roll = alpha * (roll + gyroRollRate * dt) + (1 - alpha) * accelRoll;
  pitch = alpha * (pitch + gyroPitchRate * dt) + (1 - alpha) * accelPitch;

  
  // Дебаг для тоог чтобы видеть графики
   Serial.print("Roll:"); Serial.print(roll);
   Serial.print(", Pitch:"); Serial.print(pitch);
   Serial.println("");

  // Теперь можно передать релейному контроллеру нынешнее значение угла
  // а он из него решит нужно ли корректировать
  rollController.input = roll;
  // TODO: pitchController.input = pitch;

  rollController.compute(); // очевидно
  // TODO: pitchController.compute(); 

    // Управление балластами для крена
    if (rollController.output) {
      if (roll > 2) { // Крен вправо → заполняем левый борт
        octofet.digitalWrite(4, HIGH, 0);
        octofet.digitalWrite(5, HIGH, 1);
        digitalWrite(pump2_1, HIGH);
        digitalWrite(pump2_2, LOW);

        digitalWrite(pump1_1, HIGH);
        digitalWrite(pump1_2, LOW);
       // delay(500);
      } else 
      { // Крен влево → заполняем правый борт
        //Serial.println("IMDONE");
       digitalWrite(pump2_1, LOW);
      digitalWrite(pump2_2, LOW);
      digitalWrite(pump1_1, LOW);
      digitalWrite(pump1_2, LOW);
      octofet.digitalWrite(4, LOW, 0);
      octofet.digitalWrite(5, LOW, 1);
      }
      
    } else { // Если регулировка не требуется, выключаем все
      digitalWrite(pump2_1, LOW);
      digitalWrite(pump2_2, LOW);
      digitalWrite(pump1_1, LOW);
      digitalWrite(pump1_2, LOW);
      octofet.digitalWrite(4, LOW, 0);
      octofet.digitalWrite(5, LOW, 1);
  /*
      digitalWrite(pump1_1, LOW);
      digitalWrite(pump1_2, LOW);
      digitalWrite(pump2_1, LOW);
      digitalWrite(pump2_2, LOW);
      digitalWrite(pump3_1, LOW);
      digitalWrite(pump3_2, LOW);
      digitalWrite(pump4_1, LOW);
      digitalWrite(pump4_2, LOW);*/
    }
    

    // TODO: Управлять pitch

  delay(20);
}
