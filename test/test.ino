void setup() {
  for(int i = 0; i <= 3; i++) pinMode(i, OUTPUT);

}

void loop() {
  for(int i = 0; i <= 3; i++){
    digitalWrite(i,HIGH);
    delay(1000);
    digitalWrite(i,LOW);
  }
}
