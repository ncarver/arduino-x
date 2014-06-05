/*
irSend sketch 
this code needs an IR LED connected to pin 3 
and 5 switches connected to pins 4 - 8
*/ 

#include <IRremote.h>	// IR remote control library

const int numberOfKeys = 5; 
const int firstKey = 4;	
// the first pin of the 5 sequential pins connected
// to buttons

boolean buttonState[numberOfKeys];
boolean lastButtonState[numberOfKeys]; 

long irKeyCodes[numberOfKeys] = {
  0x20DF08F7, //0 key , Value: 20DF08F7 (32 bits)
  0x20DF8877, //1 key , Value: 20DF8877 (32 bits)
  0x20DF48B7, //2 key , Value: 20DF48B7 (32 bits)
  0x20DFC837, //3 key , Value: 20DFC837 (32 bits)
  0x20DF28D7, //4 key , Value: 20DF28D7 (32 bits)
};

IRsend irsend;


void setup() {
  for (int i = 0; i < numberOfKeys; i++) { 
    buttonState[i] = true; 
    lastButtonState[i] = true; 
    int physicalPin = i + firstKey;
    pinMode(physicalPin, INPUT); 
    digitalWrite(physicalPin, HIGH); // turn on pull-ups
  }

  Serial.begin(9600);
} 

void loop() { 
  for (int keyNumber = 0; keyNumber < numberOfKeys; keyNumber++) {
    int physicalPinToRead = keyNumber + 4; 
    buttonState[keyNumber] = digitalRead(physicalPinToRead); 
    if (buttonState[keyNumber] != lastButtonState[keyNumber]) {
      if (buttonState[keyNumber] == LOW) {
        irsend.sendNEC(irKeyCodes[keyNumber], 32); 
        Serial.println("Sending");
      }
    }
    lastButtonState[keyNumber] = buttonState[keyNumber];
  }
}

