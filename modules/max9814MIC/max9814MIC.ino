int vol =0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  vol = analogRead(A0);
  Serial.println(vol);
  delay(5);
}
//Громче -> меньше