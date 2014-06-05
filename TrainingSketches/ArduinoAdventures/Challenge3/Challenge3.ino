int tempPin = 0; 
int LEDPin = 10;

void setup() {
  pinMode(LEDPin, OUTPUT); 
  Serial.begin(9600);
}

void loop() {
  //get voltage reading from the temperature sensor 
  int reading = analogRead(tempPin);
  
  // Convert voltage to Celsius 
  float tempC = 25 + (reading - 512) / 11.3;
  
  // convert Celsius to Fahrenheit 
  float tempF = (tempC * 9.0 / 5.0) + 32.0;
  
  // if Temperature is greater-than or equal to 75 turn LED on else leave 
  // LED off 
  if(tempF >= 85) {
    digitalWrite(LEDPin, HIGH);
  } else {
    digitalWrite(LEDPin, LOW);
  }
  
  // for debugging purposes shpow tempF data on Serial monitor 
  Serial.println(tempF); //Send tempF data to serial port.
  delay(1000);	//waiting a half second 
}
