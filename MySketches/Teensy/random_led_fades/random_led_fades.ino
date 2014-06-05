const int red = 12; 
const int green = 15; 
const int blue = 14;
const boolean logging = true;

long fade = 0;
int fadeStep = 10;

int redStart = 0;
int blueStart = 0;
int greenStart = 0;
float redCurrent = redStart;
float blueCurrent = blueStart;
float greenCurrent = greenStart;
int redFinish = redStart;
int blueFinish = blueStart;
int greenFinish = greenStart;
float redInc = 0;
float blueInc = 0;
float greenInc = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("setup");
  pinMode(red, OUTPUT); 
  pinMode(green, OUTPUT); 
  pinMode(blue, OUTPUT);
}

void loop() {
  Serial.println("loop");
  float diff;
  float numsteps;

  if (fade <= 0) { //initialize the values
    fade = getFadeValue();
    redStart = redCurrent;
    redFinish = getColorValue();
    greenStart = greenCurrent;
    greenFinish = getColorValue();
    blueStart = blueCurrent;
    blueFinish = getColorValue();

    numsteps = fade / fadeStep;

    diff = redFinish - redStart;
    redInc = diff / numsteps;
    diff = greenFinish - greenStart;
    greenInc = diff / numsteps;
    diff = blueFinish - blueStart;
    blueInc = diff / numsteps;
    
    Serial.print("fade divisor "); Serial.println(numsteps, DEC);
    Serial.print("redStart "); Serial.println(redStart, DEC);
    Serial.print("redFinish "); Serial.println(redFinish, DEC);
    Serial.print("redInc "); Serial.println(redInc, DEC);
    Serial.print("greenStart "); Serial.println(greenStart, DEC);
    Serial.print("greenFinish "); Serial.println(greenFinish, DEC);
    Serial.print("greenInc "); Serial.println(greenInc, DEC);
    Serial.print("blueStart "); Serial.println(blueStart, DEC);
    Serial.print("blueFinish "); Serial.println(blueFinish, DEC);
    Serial.print("blueInc "); Serial.println(blueInc, DEC);
    
  }
  
  //update the current values
  redCurrent += redInc;
  if ((redInc > 0 && redCurrent > redFinish) || (redInc < 0 && redCurrent < redFinish)) redCurrent = redFinish;
  blueCurrent += blueInc;
  if ((blueInc > 0 && blueCurrent > blueFinish) || (blueInc <0 && blueCurrent < blueFinish)) blueCurrent = blueFinish;
  greenCurrent += greenInc;
  if ((greenInc > 0 && greenCurrent > greenFinish) || (greenInc < 0 && greenCurrent < greenFinish)) greenCurrent = greenFinish;
  
  Serial.print("red "); Serial.println(redCurrent, DEC); 
  Serial.print("blue "); Serial.println(blueCurrent, DEC); 
  Serial.print("green "); Serial.println(greenCurrent, DEC);
  
  //write to analog pins
  analogWrite(red, redCurrent);
  analogWrite(blue, blueCurrent);
  analogWrite(green, greenCurrent);
  
  //decrement to new timing
  fade -= fadeStep;
  Serial.print("fade "); Serial.println(fade, DEC);
  delay(fadeStep);  
}

int getFadeValue() {
  Serial.println("getFadeValue");
  long val = random(3000, 5000);
  Serial.print("val = "); Serial.println(val, DEC);
  return (val);
}

int getColorValue() {
  Serial.println("getColorValue");
  int val = random(0, 255);
  Serial.print("val = "); Serial.println(val, DEC);
  return (val);
}

