void setup() {
  Serial.begin(9600);
  pinMode(0, INPUT_PULLUP);
  delay(5000);
}

void loop() {
  if (digitalRead(0) == LOW) {
    Keyboard.print("\n\rThanks,\n\r-Nathan\n\r");
    delay(500);
  }
}
