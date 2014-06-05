//BASICS
//there are three targets
//each target is a light sensor, when light hits the sensor, then the target is hit
//when a target is hit, it falls
//after some time, the target gets back up again

//NICE TO HAVES
//limited play time
//music
//scoring
//personality for each target -- how does it get back up, how does it fall down, does it try to evade getting hit?

/* compiler directives */
#define DEBUG true;

/* LIBRARIES */
#include <Servo.h>

/* named constants */
const int SENSOR_THRESHHOLD = 650;

/* SENSOR PINS - analog */
const int targetCount = 3;
const int minDelaySeconds = 1;
const int maxDelaySeconds = 6;
int targetSensors[] = {0,1,2};
int targetDelay[targetCount]; //how many seconds must it stay down
unsigned long targetLastLoweredTime[targetCount]; //what was the last time target was lowered

/* SERVO PINS - PWD */
int servoPins[] = {3,5,6};
Servo servos[targetCount];

/* SETUP */
void setup() {
  //setup serial
  Serial.begin(9600);
  
  #if DEBUG
  Serial.println("setup");
  delay(10000);
  #endif
  
  //setup random
  randomSeed(analogRead(0));
  
  //initialize sensors & servos
  for (int i=0; i<targetCount; i++) {
    servos[i].attach(servoPins[i]);
    lowerTarget(i);
  }
}

void raiseTarget(int targetId) {
  #if DEBUG
  Serial.print("raiseTarget");Serial.println(targetId);
  #endif
  
  servos[targetId].write(100);
}

void lowerTarget(int targetId) {
  #if DEBUG
  Serial.print("lowerTarget");Serial.println(targetId);
  #endif
  
  servos[targetId].write(10);
  targetLastLoweredTime[targetId] = millis();
  targetDelay[targetId] = random(minDelaySeconds, maxDelaySeconds);
  
  #if DEBUG
  Serial.print("Target values: ");
  Serial.print("LastLowered = ");Serial.print(targetLastLoweredTime[targetId]);
  Serial.print(", Delay = ");Serial.print(targetDelay[targetId]);
  Serial.println();
  #endif
}

/* LOOP */
#if DEBUG
boolean firstLoop = true;
#endif

void loop() {
  #if DEBUG
  if (firstLoop) {
    Serial.println("loop");
    firstLoop = false;
  }
  #endif
  
  int sensorValue;
  int servoState;
  unsigned long timeToRaise;
  
  //who is down?
  //if down, who should get up?
  for (int i=0; i<targetCount; i++) {                                 //for each target
    servoState = servos[i].read();                                    //read value for servo angle
    #if DEBUG
    Serial.print("who is down? servo ");Serial.print(i);Serial.print(" = ");Serial.println(servoState);
    #endif
    
    if (servoState <= 10) {                                           //is it down?
      timeToRaise = targetLastLoweredTime[i] + (targetDelay[i]*1000); //what time is it allowed to get up
      #if DEBUG
      Serial.print("is millis() ");Serial.print(millis());Serial.print(" > ");Serial.println(timeToRaise);
      #endif
      
      if (millis() > timeToRaise) {                                   //is time greater than time-to-wait?
        raiseTarget(i);                                               //ok - raise this target
      }
    }
  }
  
  //who is shot?
  //if shot then fall down
  for (int i=0; i<targetCount; i++) {             //for each target
    servoState = servos[i].read();                //read value for servo angle
    #if DEBUG
    Serial.print("who is up? servo ");Serial.print(i);Serial.print(" = ");Serial.println(servoState);
    #endif
    
    if (servoState >= 90) {                       //is it up?
      sensorValue = analogRead(targetSensors[i]); //what is the sensor value
      #if DEBUG
      Serial.print("sensorValue = ");Serial.println(sensorValue);
      #endif
      if (sensorValue > SENSOR_THRESHHOLD) {      //is value greater than threshhold?
        lowerTarget(i);                           //ok - lower this target
      }
    }
  }
  delay(10); //just because
}
