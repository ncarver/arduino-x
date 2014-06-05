const int numberOfButtons = 21;

void setup() {
  for (int i=0; i<numberOfButtons; i++) {
    if (i == 10) continue;
    pinMode(i, INPUT);
    digitalWrite(i, HIGH);//turn on pull-ups
  }
  Serial.begin(9600);
}

void loop() {
  for (int i=0; i<numberOfButtons; i++) {
    if (i == 10) continue;
    if (digitalRead(i) == LOW) {
      Serial.print("Button");Serial.println(i,DEC);
      delay(200);
    }
  }
}
