boolean isOn = false;
int ledPin = 13;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (isOn) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  isOn = !isOn;
  Serial.print("pin ");Serial.print(ledPin);Serial.print(" is ");Serial.println(isOn);
  delay(1000);
}  

