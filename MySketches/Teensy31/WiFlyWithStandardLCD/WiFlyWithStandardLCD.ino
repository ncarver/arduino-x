#include <stdio.h>         // uncertain if this library is needed
#include <LiquidCrystal.h> // library for the LCD commands

// initialize the LCD with the numbers of the interface pins
// use the syntax: LiquidCrystal(rs, enable, d4, d5, d6, d7) 
LiquidCrystal lcd(4, 5, 6, 7, 8, 9); 

// prepare the serial communication for debugging and for the WiFly
void setup() {
    Serial.begin(9600); //on - screen serial window
    Serial3.begin(9600);//pins for serial communication with WiFly
}

// method to output WiFly serial to LCD
void write_lines(const char *L0, const char *L1) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(L0);
    lcd.setCursor(0, 1);
    lcd.print(L1);
}

// loop to watch the WiFly
void loop() {
    if (Serial3.available()) {
        //prepare buffers for Line1 and Line2 of LCD
        char L0[17];
	char L1[17];

        //identify cursor position in buffer
	int pos = 0;

        //initialize buffers to be empty
        L0[0] = '\0';
        L1[0] = '\0';

        //loop to get information from WiFly
        while (Serial3.available()) {
            //get data on character at a time
            char c = Serial3.read();
            
            //echo character to debug console
            Serial.print((char) c);
            
            //if newline or carriage return found, then reset the cursor position
            if (c == '\n' || c == '\r') {
                pos = 0;
                
            //otherwise store the character in the line buffers    
            } else {
              
                //first 16 characters in line 1
                if (pos < 16) {
                    L0[pos] = c;
                    pos++;
                    L0[pos] = '\0';
                    
                //second 16 characters in line 2
                } else if (pos < 32) {
                    L1[pos - 16] = c;
                    pos++;
                    L1[pos - 16] = '\0';
                }
                
                //ignore messages longer than 32 characters
            }
        }
        //output to LCD
        write_lines(L0, L1);
    }
    
    //small delay before fetching next message
    delay(100);
}
