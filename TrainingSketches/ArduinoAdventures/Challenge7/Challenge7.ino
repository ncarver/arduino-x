// include the servo library so this sketch can use it 
#include <Servo.h>


// create an instance of the servo type 
Servo myServo;

// initialize the photoresistor pin 
int photoPin = 0; 
int servoPin = 3;

// create a variable to store the photoresistors value 
int photoVal = 0; 
int lightLimit = 900;

void setup() {
  // attach the servo to digital pin 3 of the Arduino 
  myServo.attach(servoPin);
  
  // begin serial communication 
  Serial.begin(9600);
  
  // set the servo to the 0 degree position 
  myServo.write(0);
}

void loop() {
// set photoVal to the reading on analog pin 0 
  photoVal = analogRead(photoPin);
  
  // if the photoresistor reads a value of 900 or higher 
  // set the servo to 0 degree position 
  // wait for a second, then set the 
  // servo to 70 degrees, then wait half a second and return 
  // the servo back to the 0 degree position
  if (photoVal >= lightLimit) {
    myServo.write(70); 
    delay(500); 
    myServo.write(0); 
    delay(500);
  } else {
    // do nothing or add your own code here
  } 
  
  // write the photoVal to the serial port for debugging purposes 
  Serial.println(photoVal);
  delay(10);
}
