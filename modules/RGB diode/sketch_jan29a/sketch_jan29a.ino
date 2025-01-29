const int PIN_RED   = 5;
const int PIN_GREEN = 6;
const int PIN_BLUE  = 9;

void setup() {
  pinMode(PIN_RED,   OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE,  OUTPUT);

}

void loop() {
  analogWrite(PIN_RED,   0);
  analogWrite(PIN_GREEN, 0);
  analogWrite(PIN_BLUE,  157);

}
