// initailize the two PWM pins to control speed for two motors
int PWMPin1 = 5;
int PWMPin2 = 6;

// initailize direction pins
int DirPin1 = 4;
int DirPin2 = 7;

// constants for forward movement
  /*
     sets DirPin1 to HIGH and PWMPin1 to 220 out of 255.
     I tweeked the PWMPin1 value to 220 rather then 255
     because the robot was turning left when it should be going
     straight. You may need to do the same to either PWMPin
     value.
  */
const int FORWARD_PWM1 = 250;
const int FORWARD_PWM2 = 255;
const int STOP_PWM1 = 0;
const int STOP_PWM2 = 0;

// function prototypes for the 5 function we need to create
void Forward(int);
void Reverse(int);
void turnRight(int);
void turnLeft(int);
void Stop(int);

void setup() {
  pinMode(PWMPin1, OUTPUT);
  pinMode(PWMPin2, OUTPUT);
  pinMode(DirPin1, OUTPUT);
  pinMode(DirPin2, OUTPUT);
}

void loop() {
  Forward(3500); //1500
//  turnRight(500);
//  Forward(2000);
//  turnLeft(750);
  Reverse(3500); //2500
  Stop(2500);
}

void Forward(int tdelay) {
   digitalWrite(DirPin1, HIGH);
   analogWrite(PWMPin1, FORWARD_PWM1);
   digitalWrite(DirPin2, HIGH);
   analogWrite(PWMPin2, FORWARD_PWM2);
   delay(tdelay);
}

void Reverse(int tdelay) {
   digitalWrite(DirPin1, LOW);
   analogWrite(PWMPin1, FORWARD_PWM1);
   digitalWrite(DirPin2, LOW);
   analogWrite(PWMPin2, FORWARD_PWM2);
   delay(tdelay);
}

void turnRight(int tdelay) {
   digitalWrite(DirPin1, LOW);
   analogWrite(PWMPin1, FORWARD_PWM1);
   digitalWrite(DirPin2, HIGH);
   analogWrite(PWMPin2, FORWARD_PWM2);
   delay(tdelay);
}

void turnLeft(int tdelay) {
   digitalWrite(DirPin1, HIGH);
   analogWrite(PWMPin1, FORWARD_PWM1);
   digitalWrite(DirPin2, LOW);
   analogWrite(PWMPin2, FORWARD_PWM2);
   delay(tdelay);
}

void Stop(int tdelay) {
   digitalWrite(DirPin1, LOW);
   analogWrite(PWMPin1, STOP_PWM1);
   digitalWrite(DirPin2, LOW);
   analogWrite(PWMPin2, STOP_PWM2);
   delay(tdelay);
}
