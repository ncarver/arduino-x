const int red = 12; 
const int green = 15; 
const int blue = 14;

int time = 1000; 
int multiple = 2;

void setup() {
  Serial.begin(9600);
  pinMode(red, OUTPUT); 
  pinMode(green, OUTPUT); 
  pinMode(blue, OUTPUT);
}

void loop() { 
  Serial.println(time);
  digitalWrite(red, HIGH); 
  delay(time); 
  digitalWrite(green, HIGH); 
  delay(time); 
  digitalWrite(red, LOW); 
  delay(time); 
  digitalWrite(blue, HIGH); 
  delay(time); 
  digitalWrite(green, LOW); 
  delay(time); 
  digitalWrite(red, HIGH); 
  delay(time); 
  digitalWrite(green, HIGH); 
  delay(time * multiple); 
  digitalWrite(blue, LOW); 
  digitalWrite(green, LOW);
  time = time - 10;
  if (time == 0) time = 1000;
}

