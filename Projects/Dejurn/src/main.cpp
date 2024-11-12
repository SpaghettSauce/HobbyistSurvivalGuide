// Подключаем необходимые компоненты
const int LED_PIN = 9;                // Пин светодиода
const int BUTTON_PIN = 2;             // Пин кнопки
const int SWITCH_PIN = 3;             // Пин переключателя
const int POTENTIOMETER_PIN = A0;     // Пин переменного резистора
const int TRIG_PIN = 4;               // Пин триггера ультразвукового датчика
const int ECHO_PIN = 5;               // Пин эхо ультразвукового датчика

// Переменные для отслеживания состояния системы
bool manualMode;                      // Режим работы: true - ручной, false - автоматический
bool ledState = false;                // Состояние светодиода
long distance;                        // Расстояние, измеренное датчиком
unsigned long lastButtonPress = 0;    // Время последнего нажатия кнопки

void setup() {
  Serial.begin(9600);                 // Настройка монитора порта
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  manualMode = digitalRead(SWITCH_PIN) == HIGH;  // Считываем начальный режим
  Serial.println("Система запущена.");
  displayMode();
}

void loop() {
  // Чтение значения потенциометра для регулировки яркости
  int brightness = analogRead(POTENTIOMETER_PIN) / 4;
  analogWrite(LED_PIN, ledState ? brightness : 0);

  // Проверка состояния переключателя для смены режима
  bool switchState = digitalRead(SWITCH_PIN);
  if (switchState != manualMode) {
    manualMode = switchState;
    displayMode();
  }

  if (manualMode) {
    // Ручной режим: реагируем на кнопку
    if (digitalRead(BUTTON_PIN) == LOW && millis() - lastButtonPress > 200) {
      ledState = !ledState;
      lastButtonPress = millis();
    }
  } else {
    // Автоматический режим: реагируем на ультразвуковой датчик
    distance = getDistance();
    ledState = (distance <= 200);
  }
}

// Функция для отображения режима в мониторе порта
void displayMode() {
  if (manualMode) {
    Serial.println("Ручной режим включен.");
  } else {
    Serial.println("Автоматический режим включен.");
  }
}

// Функция для получения расстояния от ультразвукового датчика
long getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  long distanceCm = duration * 0.034 / 2;
  return distanceCm;
}
