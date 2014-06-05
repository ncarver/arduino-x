#include<stdio.h>

void setup(){
  Serial.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);
}
 
void write_lines( const char *L0, const char *L1 ){
   
  Serial2.write( 0xFE );
  Serial2.write( 0x01 );
  delay(10);
  Serial2.write( 0xFE );
  Serial2.write( 128 );
  delay(10);
  Serial2.print( L0 );
  Serial2.write( 0xFE );
  Serial2.write( 192 );
  delay(10);
  Serial2.print( L1 );
}
 
 
void loop(){
  if( Serial3.available() ){
    char L0[17];
    char L1[17];
    int pos = 0;
 
    L0[0] = '\0';
    L1[0] = '\0';
 
    while( Serial3.available() ){
      char c = Serial3.read();
      if( c == '\n' ){
        pos = 0;
        Serial.print('\n');
      } else if( c == '\r' ){
         
      } else {
        if( pos < 16 ){
          L0[pos] = c;
          pos++;
          L0[pos] = '\0';
        } else if( pos < 32 ){
          L1[pos-16] = c; 
          pos++;  
          L1[pos-16] = '\0'; 
        }
        Serial.print( (char)c );
      }
    }
    write_lines( L0, L1 );
  }
  delay(100);
}
