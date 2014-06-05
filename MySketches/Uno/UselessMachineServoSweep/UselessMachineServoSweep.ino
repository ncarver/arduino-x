#include <Servo.h>

Servo myservo; // create servo object to control a servo 
int angle = 0; // variable to store the servo position
int servoPin = 9;
int servoStep = 90;
int servoDelay = 200;
int switchPin = 2;

void setup() {
  pinMode(switchPin, INPUT);
  myservo.attach(servoPin); // attaches the servo on pin 9 to the servo object
}

void loop() {
  
  int switchVal = digitalRead(switchPin);
  if (switchVal == HIGH) {  
    for (angle = 0; angle < 180; angle = angle + servoStep) {
      myservo.write(angle);
      delay(servoDelay);
    }
  
    for (angle = 180; angle > 0; angle = angle - servoStep) {
      myservo.write(angle);
      delay(servoDelay);
    }
  }
}

