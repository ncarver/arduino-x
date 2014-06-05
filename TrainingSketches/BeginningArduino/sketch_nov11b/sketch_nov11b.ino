const int rgb[] = {12,14,15};
const int switchPin = 2;
int i = 0;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 3; i++) {
    pinMode(rgb[i], OUTPUT);
  } 
  pinMode(switchPin, INPUT);
}

void loop() { 
  int bounce1 = digitalRead(switchPin); 
  delay(25); 
  int bounce2 = digitalRead(switchPin);
  
  if ((bounce1 == bounce2) && (bounce1 == HIGH)) { 
    Serial.println("switch triggered");
    Serial.print("set to low ");Serial.println(rgb[i]);
    digitalWrite(rgb[i], LOW);
    i++;
    if (i > 2) i = 0;
    Serial.print("set to HIGH ");Serial.println(rgb[i]);
    digitalWrite(rgb[i], HIGH); 
  } // end if

  delay(1000);
}
