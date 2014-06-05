int redPin =  12;
int greenPin =  15;
int bluePin =  14;
int bluePushButton = 7;
int redPushButton = 8;

int blueValue = 0;
int redValue = 0;
int greenValue = 0;
int blueIncrement = 1;
int redIncrement = 1;
int greenIncrement = 1;

boolean blueOn = false;
boolean redOn = false;


void setup()   {
  Serial.begin(38400);
  pinMode(bluePushButton, INPUT);
  pinMode(redPushButton, INPUT_PULLUP);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop()                     
{
  if (blueOn) {
    blueValue = blueValue + blueIncrement;
    if (blueValue > 255) {
      blueIncrement = -1;
      blueValue = 255;
    }
    if (blueValue < 0) {
      blueIncrement = 1;
      blueValue = 0;
    }
  }
  if (redOn) {
    redValue = redValue + redIncrement;
    if (redValue > 255) {
      redIncrement = -1;
      redValue = 255;
    }
    if (redValue < 0) {
      redIncrement = 1;
      redValue = 0;
    }
  }
  greenValue = greenValue + greenIncrement;
  if (greenValue > 255) {
    greenIncrement = -1;
    greenValue = 255;
  }
  if (greenValue < 0) {
    greenIncrement = 1;
    greenValue = 0;
  }
  
  // set all 3 pins to the desired intensity
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
  
  if (digitalRead(bluePushButton) == LOW) {
    // use mode zero when the first button is pressed
    blueOn = true;
    Serial.println("blueOn true");
  } else {
    blueOn = false;
  }
  if (digitalRead(redPushButton) == LOW) {
    // use mode one when the first button is pressed
    redOn = true;
    Serial.println("redOn true");
  } else {
    redOn = false;
  }
  
  // remain at this color, but not for very long
  delay(10);
  
}
