void setup() {
  pinMode(25, OUTPUT);
}

void High(){
  digitalWrite(25, HIGH);
}

void Low(){
  digitalWrite(25, LOW);
}

void Flash(int t){
  High();
  delay(t);
  Low();
}

void loop() {
  Flash(1000);
  delay(500);
  Flash(1000);
  delay(500);
  Flash(1000);
  delay(500);
  Flash(500);
  delay(500);
  Flash(500);
  delay(500);
  Flash(500);
  delay(500);
}
