//N20 это мотор с энкодером (такая круглая черная штука снизу), это магнитная деталь, позволяющая нам легко считывать и подавать значения мотору
//грубо говоря сам по себе мотор с энкодером это самый умный мотор, поскольку он знает своё положение и направление (<-- то что нужно для ракеты), 
//а ещё конпенсировать если мотор крутиться слишком медленно или быстро(к примеру если кто-то его остановит пальцем, энкодер это заметит и компенсирует)

//когда энкодер крутиться, он выдает значения с периодом (см. картинку период), когда значение А подается первым, то мотор крутиться по часовой стрелке и наоборот


#define MotFwd  3  // Пин мотора движения по часовой стрелке
#define MotRev  4 // Пин мотора движения против часовой стрелке

int encoderPin1 = 2; //Первый пин энкодера
int encoderPin2 = 3; //Второй пин энкодера
volatile int lastEncoded = 0; //здесь будем хранить наши обновленные значения энкодера
volatile long encoderValue = 0; // Здесь будут "сырые" значения энкодера


void setup() {

  pinMode(MotFwd, OUTPUT); 
  pinMode(MotRev, OUTPUT); 
  Serial.begin(9600); 

  pinMode(encoderPin1, INPUT_PULLUP); //INPUT pinmode для энкодера
  pinMode(encoderPin2, INPUT_PULLUP);

  digitalWrite(encoderPin1, HIGH); 
  digitalWrite(encoderPin2, HIGH); 

  attachInterrupt(0, updateEncoder, CHANGE); //это нужно чтобы энкодер обновлял свои значения, в случае возникновения ошибки
  attachInterrupt(1, updateEncoder, CHANGE);


}

void loop() {

for (int i = 0; i <= 500; i++){ 
  digitalWrite(MotFwd, LOW); //не крутись по часовой
  digitalWrite(MotRev, HIGH); //крутись против часовой
  Serial.print("Назад  ");
  Serial.println(encoderValue);
}

delay(1000);

for (int i = 0; i <= 500; i++){
  digitalWrite(MotFwd, HIGH); //крутись по часовой
  digitalWrite(MotRev, LOW); //не крутись против часовой
  Serial.print("Вперед  ");
  Serial.println(encoderValue);
}

delay(1000);

} 

void updateEncoder(){ //функция для обновления значений энкодера
  int MSB = digitalRead(encoderPin1); 
  int LSB = digitalRead(encoderPin2); 

  int encoded = (MSB << 1) |LSB; 
  int sum  = (lastEncoded << 2) | encoded; 

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue --;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue ++;

  lastEncoded = encoded; 

}