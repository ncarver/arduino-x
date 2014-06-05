// Initalize buzzer and PIR sensor pins 
int buzzerPin = 9; 
int PIRPin = 6;

// Initialize PIR sensor state 
int PIRState = 0;

void setup() {
  // Set PIR sensor to an Input and the buzzer to an Output 
  pinMode(PIRPin, INPUT); 
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  // Read in PIR state (0 or 1) 
  PIRState = digitalRead(PIRPin);
  //Serial.print("PIRState = ");Serial.println(PIRState);
  // If PIRState detects motion? 
  if (PIRState == 1) {
    // Buzzer makes noise 
    tone(buzzerPin, 1000, 100);
//    digitalWrite(buzzerPin, HIGH);
  } else {
    // Buzzer makes no noise 
    digitalWrite(buzzerPin, LOW);
  }
  delay(500);
}
