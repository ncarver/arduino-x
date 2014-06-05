const int rgb[] = {12,14,15};
const int time = 250;
const int switchPin = 2;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 3; i++) {
    pinMode(rgb[i], OUTPUT);
  } 
  pinMode(switchPin, INPUT);
}

void loop() { 
  int newPin = 0; 
  int oldPin = 0;

  int bounce1 = digitalRead(switchPin); 
  delay(25); 
  int bounce2 = digitalRead(switchPin);
  
  while ((bounce1 == bounce2) && (bounce1 == HIGH)) { 
    Serial.println("switch triggered");
    oldPin = newPin; 
    newPin++;
    if (newPin == 3) {
      newPin = 0;
    }
    
    Serial.print("oldPin is ");Serial.println(oldPin);
    Serial.print("newPin is ");Serial.println(newPin);
    digitalWrite(rgb[oldPin], HIGH); 
    delay(time); 
    digitalWrite(rgb[newPin], HIGH); 
    delay(time); 
    digitalWrite(rgb[oldPin], LOW);
  
    if (newPin == 0) { 
      for (int i=0; i<3; i++) {
        digitalWrite(rgb[i], HIGH); 
      }
      delay(time); 
      for (int i=0; i<3; i++) {
        digitalWrite(rgb[i], LOW);
      }
    } //end if
    
    bounce1 = digitalRead(switchPin); 
    delay(25); 
    bounce2 = digitalRead(switchPin);
  } // end while 

  for (int i = 0; i < 3; i++) {
    digitalWrite(rgb[i], LOW); 
  }
  delay(25);
}
