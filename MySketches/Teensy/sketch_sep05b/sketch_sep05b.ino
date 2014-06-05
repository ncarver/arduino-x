int redPin =  12;
int greenPin =  15;
int bluePin =  14;

// The setup() method runs once, when the sketch starts

void setup()   {                
  // initialize the digitals pin as an outputs
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

// the loop() method runs over and over again,

void loop()                     
{
  int redValue = 0;
  int greenValue = 255;
  int blueValue = 0;
  
  for (int i = 0; i<256; i++) {
    analogWrite(redPin, redValue+i);
    analogWrite(greenPin, greenValue-i);
    analogWrite(bluePin, blueValue+i);
    delay(10);
  }
  delay(500);
}
