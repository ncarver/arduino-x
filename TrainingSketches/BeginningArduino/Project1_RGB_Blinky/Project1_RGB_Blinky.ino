/* Project 1: RGB Blinky 
   Uses a single RGB LED to cycle through three colors.
*/

int redPin = 12;
int greenPin = 15;
int bluePin = 14;

void setup() { 
  Serial.begin(9600);          //prepare console
  pinMode(redPin, OUTPUT);     //sets digital pins as outputs
  pinMode(greenPin, OUTPUT); 
  pinMode(bluePin, OUTPUT);
}
void loop() {
  Serial.println("turn on red");
  digitalWrite(redPin, HIGH);  // turns on red
  digitalWrite(bluePin, LOW);  // turns off blue 
  delay(1000);                 // wait
  Serial.println("turn on green");
  digitalWrite(greenPin, HIGH);// turns on green
  digitalWrite(redPin, LOW);   // turns off red
  delay(1000);                 // wait
  Serial.println("turn on blue");
  digitalWrite(bluePin, HIGH); // turns on blue
  digitalWrite(greenPin, LOW); // turns off green
  delay(1000);                 // wait
}
