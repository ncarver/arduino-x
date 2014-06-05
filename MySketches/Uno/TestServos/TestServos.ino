/* LIBRARIES */
#include <Servo.h>

/* SERVO PINS - PWD */
const int SERVO_COUNT = 3;
int servoPins[] = {3,5,6};
int servoAngle = 0;
Servo servos[SERVO_COUNT];

/* SETUP */
void setup() {
  //setup serial
  Serial.begin(9600);
  Serial.println("setup");
  delay(5000);
  
  //initialize servos
  for (int i=0; i<SERVO_COUNT; i++) {
    Serial.print("attach servo ");Serial.println(i);
    servos[i].attach(servoPins[i]);
    moveServo(i, servoAngle);
  }
}

void moveServo(int servoId, int degree) {
  Serial.print("moveServo");Serial.print(servoId);Serial.print(" to ");Serial.println(degree);
  servos[servoId].write(degree);
}


/* LOOP */
void loop() {
  servoAngle = servoAngle + 10;
  if (servoAngle > 180) servoAngle = 0;
  Serial.print("servoAngle = ");Serial.println(servoAngle);
  
  for (int i=0; i<SERVO_COUNT; i++) {                                 //for each target
    moveServo(i, servoAngle);
  }  
  delay(1000);
}
