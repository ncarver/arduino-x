/*
12 CHANNEL TV REMOTE CONTROL

ABC, CBS, NBC, FOX, PBS, MY9, PIX, NY1, TBS, WLIW, VolUp, VolDown, Power, Mute

this code needs an IR LED connected to pin 10 (teensy 2.0)
and 14 switches connected to pins 0 - 6 & 14 - 20 
*/

#include <IRremote.h>	// IR remote control library

boolean logit = true;
const int lowerButtonsStart = 0;
const int lowerButtonsEnd = 7;
const int upperButtonsStart = 14;
const int upperButtonsEnd = 21;
const int numberOfCommands = 14;
long irKeyCodes[numberOfCommands] = {
  0x20DF08F7, //0 key , Value: 20DF08F7 (32 bits)
  0x20DF8877, //1 key , Value: 20DF8877 (32 bits)
  0x20DF48B7, //2 key , Value: 20DF48B7 (32 bits)
  0x20DFC837, //3 key , Value: 20DFC837 (32 bits)
  0x20DF28D7, //4 key , Value: 20DF28D7 (32 bits)
  
  0x20DFA857, //5 key , Value: 20DFA857 (32 bits)
  0x20DF6897, //6 key , Value: 20DF6897 (32 bits)
  0x20DFE817, //7 key , Value: 20DFE817 (32 bits)
  0x20DF18E7, //8 key , Value: 20DF18E7 (32 bits)
  0x20DF9867, //9 key , Value: 20DF9867 (32 bits)
  
  0x20DF40BF, //a key - volume up,   Value: 20DF40BF (32 bits)
  0x20DFC03F, //b key - volume down, Value: 20DFC03F (32 bits)
  0x20DF10EF, //c key - power,       Value: 20DF10EF (32 bits)
  0x20DF906F, //d key - mute,        Value: 20DF906F (32 bits)
};

String buttons[upperButtonsEnd] = {
  // 0 = mute
  "d",     //mute
  // 1 = PBS
  "622",   //pbs
  // 2 = FOX
  "613",   //fox
  // 3 = NBC
  "611",   //nbc
  // 4 = CBS
  "621",   //cbs
  // 5 = volume Up
  "a",     //volumeUp
  // 6 = ABC
  "651",   //abc
  
  // 7-13 = skip
  "",      //7-skip
  "",      //8-skip
  "",      //9-skip
  "",      //10-skip
  "",      //11-skip
  "",      //12-skip
  "",      //13-skip -- swap with 15

  //14 = volume Down
  "b",     //volumeDown
  //15 = power -- swap with 13
  "c",     //power
  //16 = MY9
  "654",   //my9
  //17 = PIX
  "861",   //pix11
  //18 = NY1
  "307",   //ny1
  //19 = ION
  "863", //ion
  //20 = WLIW
  "1111",  //wliw
};

IRsend irsend;

void setup() {
  Serial.begin(9600);
  if (logit) Serial.println("setup");
  for (int i = lowerButtonsStart; i < lowerButtonsEnd; i++) { 
    pinMode(i, INPUT);
    digitalWrite(i, HIGH); // turn on pull-ups
  }
  for (int i = upperButtonsStart; i < upperButtonsEnd; i++) { 
    if (i == 15) i = 13;
    pinMode(i, INPUT);
    digitalWrite(i, HIGH); // turn on pull-ups
    if (i == 13) i = 15;
  }
}

unsigned char convertCharToHex(unsigned char hex) {
  if (logit) Serial.println("converCharToHex");
  if(hex > 0x39) hex -= 7; // adjust for hex letters upper or lower case
  return(hex & 0xf);
}

int sendMyCode(int buttonNumber) {
  if (logit) Serial.println("sendMyCode");
  String stringCode = buttons[buttonNumber];

  if (logit) {
    Serial.print("Sending ");Serial.println(buttons[buttonNumber]);
  }
  
  for (int i = 0; i < stringCode.length(); i++) {
    char charCode = stringCode.charAt(i);
    int keyCode = convertCharToHex(charCode);
    irsend.sendNEC(irKeyCodes[keyCode], 32); 
    if (logit) {
      Serial.print("Sent ");Serial.print(charCode);Serial.print(",");Serial.println(irKeyCodes[keyCode]);
    }
    delay(250);
  }
  Serial.println();
}

void loop() {
  for (int i = lowerButtonsStart; i < lowerButtonsEnd; i++) {
    if (digitalRead(i) == LOW) {
      if (logit) {
        Serial.print("found lower pin ");Serial.println(i, DEC);
      }
      sendMyCode(i);

      if (i == 5) {       //short delay for volume buttons
        delay(80);
      } else {            //long delay for channel buttons
        delay(1000);
      }
    }
  }
  for (int i = upperButtonsStart; i < upperButtonsEnd; i++) {
    if (i == 15) i = 13;
    if (digitalRead(i) == LOW) { 
      if (logit) {
        Serial.print("found upper pin");Serial.println(i, DEC);
      }
      if (i == 13) i = 15;
      sendMyCode(i);

      if (i == 14) {      //short delay for volume buttons
        delay(80);
      } else {            //long delay for channel buttons
        delay(1000);
      }
    }
    if (i == 13) i = 15;
  }
}

