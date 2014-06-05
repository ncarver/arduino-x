/*
1 Button TV REMOTE CONTROL

Power

this code needs an IR LED connected to pin 10 (Teensy)
and 1 switches connected to pins 20
*/

#include <IRremote.h>	// IR remote control library

const int switchPin = 15;
const int ledPin = 11;
long powerCmd = 0x20DF10EF;
IRsend irsend;

void setup() {
  Serial.begin(9600);
  pinMode(switchPin, INPUT); 
  digitalWrite(switchPin, HIGH); // turn on pull-ups
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void loop() { 
  if (digitalRead(switchPin) == LOW) {
    irsend.sendNEC(powerCmd, 32);
    digitalWrite(ledPin, HIGH);
    delay(250);
  }
  digitalWrite(ledPin, LOW);
}

