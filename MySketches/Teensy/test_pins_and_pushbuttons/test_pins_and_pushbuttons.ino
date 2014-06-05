void setup() {                
  Serial.begin(38400);
  pinMode(7, INPUT);
  pinMode(8, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(7) == HIGH) {
    Serial.println("Button is not pressed...");
  } else {
    Serial.println("Got It!!!");
  }
  
  if (digitalRead(8) == HIGH) {
    Serial.println("Pin8 high");
  } else {
    Serial.println("Pin8 low");
  }
  
  delay(250);
}
