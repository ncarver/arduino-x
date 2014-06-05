#include <SoftwareSerial.h> //Sketch Arduino WiFi for Wifly modem communication without Wifly library
/***************************************************************************
Firmware and Front-end: https://dl.dropboxusercontent.com/u/101922388/WiflySanUSB.zip
APK: https://play.google.com/store/apps/details?id=appinventor.ai_sandro_juca.Wifi_SanUSB
Video http://www.youtube.com/watch?v=gUe24X1gNVw 

After uploading or reset, wait until only the green led on the Wifly modem is blinking and click connect on the front-end.
Após o upload ou reset, aguarde ate que somente o led verde do modem Wifly esteja piscando e clique em conectar no front-end
Se for a primeira gravação do PIC com modem conectado, talvez seja necessário resetar o microcontrolador após a gravação, retirando e colocando o cabo USB novamente.
//Ao digitar 192.168.1.195/YT na barra de endereço de qualquer navegador (browser), o sinal do LED será comutado (toggle) e aparecerá uma página HTML.
 **********************************************************************************/

/***After uploading or reset, wait until only the green led on the Wifly modem is blinking and click connect on the front-end.
 /***Após o upload ou reset, aguarde ate que somente o led verde do modem Wifly esteja piscando e clique em conectar no front-end***/
 
/* Static and fixed pin connection with Arduino: https://dl.dropboxusercontent.com/u/101922388/WiflySanUSB/WiflyArdCircuit.png
Arduino----------------------Wifly RN-XV
PIN 2 (soft Rx)------------- Dout or TX(2)
PIN 1 (soft Tx)------------  Din or RX(3)
3.3V ------------------------VCC (only 3.3V)
GND--------------------------GND
 ****************************************tinyurl.com/SanUSB****************************************/

SoftwareSerial Wifly(2, 1); //fixed pin connection -  Arduino Uno pin 2 (soft Rx)  <-   pin 2 RN-XV(Dout or Tx); 
char comando[128];          //                        Arduino Uno pin 1 (soft Tx)  ->   pin 3 RN-XV(Din or Rx). 
 
  unsigned char pg[] = {144,168,168,160,94,98,92,98,64,100,96,96,64,158,150,26,20,134,222,220,232,202,220,232,90,168,242,224,202,116,64,232,202,240,232,94,
  208,232,218,216,26,20,26,20,120,198,202,220,232,202,228,124,120,144,98,124,148,222,210,220,64,232,210,220,242,234,228,216,92,198,222,218,94,166,194,220,
  170,166,132,120,94,194,124,120,94,144,98,124,120,160,124,64,172,210,230,210,232,64,120,194,64,208,228,202,204,122,68,208,232,232,224,116,94,94,230,194,
  220,234,230,196,92,196,216,222,206,230,224,222,232,92,198,222,218,68,124,230,194,220,234,230,196,92,196,216,222,206,230,224,222,232,92,198,222,218,120,
  94,194,124,120,94,160,124,120,94,198,202,220,232,202,228,124,26,20,0}; 
  /* pg is Page Response: HTTP/1.1 200 OK Content-Type: text/html <center><H1>Join tinyurl.com/SanUSB</a></H1><P> Visit <a href="http://sanusb.blogspot.com">sanusb.blogspot.com</a></P></center> */
  
short int flag=0, c=0, flagsw=0, flagBD=0, led=0, pisca=0, AT1=0,  AT2=0, start=0;
unsigned char n, s, k;

char IDnet[] = "CarverFamily";         // Your WiFi SSID name 
char pass[] = "500west111";        // Your WiFi password
char ip[] = "192.168.1.195";     // Set intranet static IP (DHCP OFF). In this the case the static IP .195 is based on the gateway IP 192.168.1.1.
                                 // To check the IP of your gateway, type ipconfig or ifconfig at the prompt or terminal on the computer 
                                 // Default Wifly RN-XV SanUSB IP: 192.168.1.195 Port: 80. The Wifly IP must be xxx.xxx.x.1xx , with "1" in last byte for the gateway IP.
void setup() {
  pinMode(13, OUTPUT);             // led
  Wifly.begin(9600);               // Anfassen   
  taxa_serial(9600);               // schicken
  delay(2000);
  iniws();
}
 
void loop() {
  if (Wifly.available()) {
    comando[n]=Wifly.read();

//***************possibility 1->character***********************
    if (comando[n-1] == 'Y') {
      comando[0]== 32;

      switch (comando[n]){ 

        case 'L':  
          digitalWrite(13,HIGH); //type in browser address bar: 192.168.1.195/YL
          flagsw=1;
          break;

        case 'D': 
          digitalWrite(13,LOW); //type in browser address bar: 192.168.1.195/YD
          break;

        case 'P':  
          digitalWrite(13,HIGH); //type in browser address bar: 192.168.1.195/YP
          break;
  
        case 'T': 
          led=!led; 
          digitalWrite(13, led); //type in browser address bar: 192.168.1.195/YT to toggle Led and open a HTML page
          flagsw=1;
          break;

        case 'Y': 
          {
            n=0;
            comando[0] = 'Y';
          }
          break;
      } //switch
    }//if comando == 'Y'
    
//***************possibility 2-> word**************************
    if (comando[n-1] == 'O' && comando[n]== 'N') {
      digitalWrite(13, HIGH);   // Led ON
    }
   
    if (comando[n-2]== 'O' && comando[n-1]== 'F' && comando[n]== 'F') {
      digitalWrite(13, LOW);  // Led OFF
    }

    ++n; 
    if (n >= 128) {
      n=0;
    }
  }//if Wifly.available
  
  if (flagsw == 1) {
    flagsw = 0;
    delay(500);
    sends(pg); //send web page
    delay(500);
  }
}//loop

/* HELPER FUNCTIONS */
void sends (unsigned char st[]) {
  for (k = 0; st[k] != '\0'; k++) {
    sputc(st[k]);
  }
}

       
void taxa_serial(unsigned long baud) {
  unsigned int baud_sanusb = (F_CPU / 16 / baud) - 1;
  UBRR0H = (unsigned char)(baud_sanusb >> 8);
  UBRR0L = (unsigned char)baud_sanusb;
  UCSR0B |= _BV(RXEN0) | _BV(TXEN0);
  UCSR0B |= _BV(RXCIE0);
  UCSR0B &= ~_BV(TXCIE0);
  UCSR0C |= _BV(UCSZ01) | _BV(UCSZ00);
}

void swputc(char c) {
  loop_until_bit_is_set(UCSR0A, UDRE0); //wait for UART
  UDR0 = UBRR0H + c;
}

void sputc(unsigned char c) {
  loop_until_bit_is_set(UCSR0A, UDRE0); //wait for UART
  UDR0 = c>>UCSZ00 + UBRR0H; 
}

void iniws(void) { 
  unsigned char i = 17;
  UBRR0L = 0x33;
  unsigned int baud1 = (F_CPU/16/(UBRR0H+UBRR0L+1))-30; 
  Wifly.begin(baud1); 
  delay(1000);

  //send command-mode string
  sputc(56+i);sputc(56+i);sputc(56+i); //$$$
  
  //flash the LED on Arduino pin 13
  led = !led;
  digitalWrite(13, led);
  delay (500);
  led = !led; 
  digitalWrite(13, led);
  
  //confirm success
  while (Wifly.available()) {
    comando[n] = Wifly.read();
    if (comando[n] == 67) {
      AT1 = 1;
    } 
    ++n;
  }
  
  //if not successful, keep trying
  while (AT1 == 0) { 
    UBRR0L = 0x67;
    baud1 = (F_CPU/16/(UBRR0H+UBRR0L+1))-15;
    Wifly.begin(baud1); 
    delay(4000);
    
    while (Wifly.available()) {
      comando[n] = Wifly.read(); 
      if (comando[n] == 67) {
        AT1 = 1;
      } 
      ++n;
    }
    
    //send command-mode string
    sputc(56+i);sputc(56+i);sputc(56+i); //$$$
    
    //flash led
    n=0;
    led = !led; 
    digitalWrite(13, led);
    delay(500);
  }
  
  n = 0;
  AT1 = 0;
  --i;

  //send a factory reset
  sputc(189+i);sputc(194);sputc(198);sputc(232);sputc(222);sputc(228);
  sputc(242);sputc(64);sputc(164);sputc(26); //factory R (factory reset)
  
  //flash arduino led
  delay (1000);
  led = !led; 
  digitalWrite(13, led);
  
  //confirm success
  while (Wifly.available()) {
    comando[n]=Wifly.read(); 
    if (comando[n] == 83) {
      AT1 = 1;
    } 
    ++n;
  }
  
  //if not successful, keep trying
  while (AT1 == 0) {
    delay (1000);
    while (Wifly.available()) {
      comando[n] = Wifly.read();
      if (comando[n] == 83) {
        AT1=1;
      } 
      ++n;
    }
     
    sputc(189+i);sputc(194);sputc(198);sputc(232);sputc(222);sputc(228);
    sputc(242);sputc(64);sputc(164);sputc(26); //factory R (factory reset)
    
    led= !led; 
    digitalWrite(13, led);
  }
  n=0;
  AT1=0;
  --i;

  //set the IP Address
  sputc(216+i);sputc(202);sputc(232);sputc(64);sputc(210);sputc(64);sputc(194);
  swputc(32);swputc(ip[0]);swputc(ip[1]);swputc(ip[2]);swputc(ip[3]);
  swputc(ip[4]);swputc(ip[5]);swputc(ip[6]);swputc(ip[7]);swputc(ip[8]);
  swputc(ip[9]);swputc(ip[10]);swputc(ip[11]);swputc(ip[12]);
  swputc(ip[13]);sputc(26); //set i a *.*.*.* (set ip address)
     
  //flash arduino led
  delay(1000); 
  led= !led; 
  digitalWrite(13, led);
  
  //confirm success
  while (Wifly.available()) {
    comando[n] = Wifly.read();
    if (comando[n] == 65) {
      AT1 = 1;
    } 
    ++n;
  }
  
  //if not successful, keep trying
  while (AT1==0) { 
    delay (1000);
    while (Wifly.available()) {
      comando[n] = Wifly.read();
      if (comando[n] == 65) { 
        AT1 = 1;
      } 
      ++n;
    }
    sputc(216+i);sputc(202);sputc(232);sputc(64);sputc(210);sputc(64);sputc(194);
    swputc(32);swputc(ip[0]);swputc(ip[1]);swputc(ip[2]);swputc(ip[3]);
    swputc(ip[4]);swputc(ip[5]);swputc(ip[6]);swputc(ip[7]);swputc(ip[8]);
    swputc(ip[9]);swputc(ip[10]);swputc(ip[11]);swputc(ip[12]); 
    swputc(ip[13]);sputc(26); //set i a *.*.*.* (set ip address)
     
    led = !led;
    digitalWrite(13, led);
  }
  n = 0;
  AT1 = 0;
  --i;

  //set the IP Gateway
  sputc(217+i);sputc(202);sputc(232);sputc(64);sputc(210);sputc(64);sputc(206);
  sputc(64);swputc(ip[0]);swputc(ip[1]);swputc(ip[2]);swputc(ip[3]);
  swputc(ip[4]);swputc(ip[5]);swputc(ip[6]);swputc(ip[7]);swputc(ip[8]);
  swputc(ip[9]);  //set i g *.*.*.* (set ip gateway)
  if (ip[9] == 46) {
    swputc(ip[10]);
  } else {
    swputc(ip[10]);
    swputc(ip[11]);
  } sputc(26);
     
  //flash the arduino led
  delay(1000); 
  led = !led; 
  digitalWrite(13, led);
  
  //confirm success
  while (Wifly.available()) {
    comando[n] = Wifly.read();
    if (comando[n] == 65) {
      AT1 = 1;
    }
    ++n;
  }
  
  //if not successful, keep trying
  while (AT1==0){ delay (1000);
    while (Wifly.available()) {
      comando[n] = Wifly.read();
      if (comando[n] == 65) {
        AT1 = 1;
      } 
      ++n;
    }
    sputc(217+i);sputc(202);sputc(232);sputc(64);sputc(210);sputc(64);sputc(206);
    sputc(64);swputc(ip[0]);swputc(ip[1]);swputc(ip[2]);swputc(ip[3]);
    swputc(ip[4]);swputc(ip[5]);swputc(ip[6]);swputc(ip[7]);swputc(ip[8]);
    swputc(ip[9]);  //set i g *.*.*.* (set ip gateway)
    if (ip[9] == 46) {
      swputc(ip[10]);
    } else {
      swputc(ip[10]);
      swputc(ip[11]);
    } sputc(26);
    
    led = !led;
    digitalWrite(13, led);
  }
  AT1=0;
  --i;

  //Turn off DHCP
  sputc(218+i);sputc(202);sputc(232);sputc(64);sputc(210);sputc(64);
  sputc(200);sputc(64);sputc(96);sputc(26); //set i d 0 (set ip dhcp 0 = Turns DHCP off)
  
  //flash arduino led
  delay(500);
  led = !led;
  digitalWrite(13, led);
  
  //confirm success
  while (Wifly.available()) {
    comando[n] = Wifly.read();
    if (comando[n] == 65) {
      AT1 = 1;
    } 
    ++n;
  }
  
  //if not successful, keep trying
  while (AT1==0) {
    delay (1000);
    while (Wifly.available()) {
      comando[n] = Wifly.read();
      if (comando[n] == 65) {
        AT1=1;
      } 
      ++n;
    }
    putc(218+i);sputc(202);sputc(232);sputc(64);sputc(210);sputc(64);
    putc(200);sputc(64);sputc(96);sputc(26); //set i d 0 (set ip dhcp 0 = Turns DHCP off)
     
    led = !led;
    digitalWrite(13, led);
  }
  n=0;
  AT1=0;
  --i;

/*
  //set UART baud rate
  sputc(219+i);sputc(202);sputc(232);sputc(64);sputc(234);sputc(64);
  sputc(196);sputc(64);sputc(98);sputc(114);sputc(100);sputc(96);
  sputc(96);sputc(26); //set u b 19200 (set uart baudrate 19200)
    
  // flash arduino led
  delay (1000); 
  led= !led; 
  digitalWrite(13, led); 
  
  //set protocol to include TCP client/server
  sputc(219+i);sputc(202);sputc(232);sputc(64);sputc(210);sputc(224); 
  sputc(64);sputc(224);sputc(228);sputc(222);sputc(232);sputc(222); 
  sputc(64);sputc(98);sputc(112);sputc(26); //set ip proto 1 (set ip protocol 1 == TCP client/server)

  // flash arduino led    
  delay (1000);  
  led = !led; 
  digitalWrite(13, led);

  //Rename device id
  sputc(219+i);sputc(202);sputc(232);sputc(64);sputc(222);sputc(64);
  sputc(200);sputc(64);sputc(166);sputc(194);sputc(220);sputc(170);
  sputc(166);sputc(132);sputc(90);sputc(204);sputc(216);sputc(242);sputc(26); 
  //set o d SanUSB-fly (set opt deviceid SanUSB-fly)

  //flash arduino led    
  delay (500); 
  led = !led; 
  digitalWrite(13, led);
*/

  //send SAVE command
  sputc(219+i);sputc(194);sputc(236);sputc(202);sputc(26); //save
  
  //flash arduino led
  delay (1000); 
  led = !led; 
  digitalWrite(13, led);
  
  //confirm
  while (Wifly.available()) {
    comando[n] = Wifly.read(); 
    if (comando[n] == 65) {
      AT1=1;
    } 
    ++n;
  }
  
  //if save not successful, keep trying
  while (AT1==0) {
    delay (1000);
    while (Wifly.available()) {
      comando[n] = Wifly.read();
      if (comando[n] == 65) {
        AT1=1;
      } 
      ++n;
    }
    
    sputc(219+i);sputc(194);sputc(236);sputc(202);sputc(26); //save
    
    led = !led; 
    digitalWrite(13, led);
  }
  AT1 = 0;
  --i;

  //send REBOOT command
  sputc(218+i);sputc(202);sputc(196);sputc(222);sputc(222);sputc(232);
  sputc(26); //reboot

  //flash arduino led
  delay (1000); 
  led = !led;
  digitalWrite(13, led);
  
  //confirm
  while (Wifly.available()) {
    comando[n]=Wifly.read();
    if (comando[n] == 111) {
      AT1 = 1;
    } 
    ++n;
  }
  
  //if not successful, keep trying
  while (AT1 == 0) {
    delay (1000);
    while (Wifly.available()) {
      comando[n] = Wifly.read();
      if (comando[n] == 111) {
        AT1 = 1;
      } 
      ++n;
    }
    
    sputc(218+i);sputc(202);sputc(196);sputc(222);sputc(222);sputc(232);  //reboot
    n=0;
    
    led = !led; 
    digitalWrite(13, led);
  }
  //reset for next command
  AT1 = 0;
  --i;
  
  //reconnect to WiFly
  UBRR0L = 0x33; 
  baud1 = (F_CPU/16/(UBRR0H+UBRR0L+1))-30; 
  Wifly.begin(baud1);
  
  //send command-mode string
  sputc(63+i);sputc(63+i);sputc(63+i); //$$$
    
  //flash arduino led
  led = !led; 
  digitalWrite(13, led);
  delay (500);
  led = !led;
  digitalWrite(13, led);
  
  //confirm
  while (Wifly.available()) {
    comando[n] = Wifly.read();
    if (comando[n] == 67) {
      AT1 = 1;
    } 
    ++n;
  }
  
  //if not successul, keep trying
  while (AT1 == 0) { 
    delay (1000);
    while (Wifly.available()) {
      comando[n] = Wifly.read(); 
      if (comando[n] == 67) {
        AT1 = 1;
      } 
      ++n;
    }
    
    sputc(63+i);sputc(72);sputc(72); //$$$
    led = !led; 
    digitalWrite(13, led);
  }
  
  n=0;
  AT1=0;
  --i;

  //Set the SSID
  sputc(222+i);sputc(202);sputc(232);sputc(64);sputc(238);sputc(64);
  sputc(230);sputc(64);swputc(IDnet[0]);swputc(IDnet[1]);swputc(IDnet[2]);
  swputc(IDnet[3]);swputc(IDnet[4]);swputc(IDnet[5]);swputc(IDnet[6]);
  swputc(IDnet[7]);swputc(IDnet[8]);swputc(IDnet[9]);swputc(IDnet[10]);
  swputc(IDnet[11]);swputc(IDnet[12]);swputc(IDnet[13]);swputc(IDnet[14]);
  swputc(IDnet[15]);swputc(IDnet[16]);sputc(26); //set w s IDnet (set wlan ssid IDnet-string)

  //flash arduino led   
  delay (500); 
  led = !led; 
  digitalWrite(13, led);
  
  //confirm
  while (Wifly.available()) {
    comando[n]=Wifly.read(); 
    if (comando[n] == 65) {
      AT1 = 1;
    } 
    ++n;
  }
  
  //if not successful, keep trying
  while (AT1==0) {
    delay (1000);
    while (Wifly.available()) {
      comando[n] = Wifly.read();
      if (comando[n] == 65) {
        AT1 = 1;
      } 
      ++n;
    }
    sputc(222+i);sputc(202);sputc(232);sputc(64);sputc(238);sputc(64);
    sputc(230);sputc(64);swputc(IDnet[0]);swputc(IDnet[1]);swputc(IDnet[2]);
    swputc(IDnet[3]);swputc(IDnet[4]);swputc(IDnet[5]);swputc(IDnet[6]);
    swputc(IDnet[7]);swputc(IDnet[8]);swputc(IDnet[9]);swputc(IDnet[10]);
    swputc(IDnet[11]);swputc(IDnet[12]);swputc(IDnet[13]);swputc(IDnet[14]);
    swputc(IDnet[15]);swputc(IDnet[16]);sputc(26); //set w s IDnet (set wlan ssid ssid-string)
      
    delay (500); 
    led = !led;
    digitalWrite(13, led);
  }
  n = 0;
  AT1 = 0;
  --i;

  //set the password
  sputc(223+i);sputc(202);sputc(232);sputc(64);sputc(238);sputc(64);
  sputc(224);sputc(64);swputc(pass[0]);swputc(pass[1]);swputc(pass[2]);
  swputc(pass[3]);swputc(pass[4]);swputc(pass[5]);swputc(pass[6]);
  swputc(pass[7]);swputc(pass[8]);swputc(pass[9]);swputc(pass[10]);
  swputc(pass[11]);swputc(pass[12]);swputc(pass[13]);swputc(pass[14]);
  swputc(pass[15]);swputc(pass[16]);sputc(26); //set w p pass (set wlan pass password-string)
    
  //flash the arduino led
  delay (500); 
  led = !led; 
  digitalWrite(13, led);
  
  //confirm
  while (Wifly.available()) {
    comando[n] = Wifly.read();
    if (comando[n] == 65) {
      AT1 = 1;
    } 
    ++n;
  }
  
  //if not successful, keep trying
  while (AT1 == 0) {
    delay (1000);
    while (Wifly.available()) {
      comando[n] = Wifly.read();
      if (comando[n] == 65) {
        AT1 = 1;
      } 
      ++n;
    }
    
    sputc(223+i);sputc(202);sputc(232);sputc(64);sputc(238);sputc(64);
    sputc(224);sputc(64);swputc(pass[0]);swputc(pass[1]);swputc(pass[2]);
    swputc(pass[3]);swputc(pass[4]);swputc(pass[5]);swputc(pass[6]);
    swputc(pass[7]);swputc(pass[8]);swputc(pass[9]);swputc(pass[10]);
    swputc(pass[11]);swputc(pass[12]);swputc(pass[13]);swputc(pass[14]);
    swputc(pass[15]);swputc(pass[16]);sputc(26); //set w p pass (set wlan pass password-string)
    
    delay(500); 
    led = !led; 
    digitalWrite(13, led);
  }
  n = 0;
  AT1 = 0;
  --i;

/*
  //Set the UART command for port opened
  sputc(224+i);sputc(202);sputc(232);sputc(64);sputc(198);sputc(222);
  sputc(218);sputc(218);sputc(64);sputc(222);sputc(224);sputc(202);
  sputc(220);sputc(64);sputc(84);sputc(166);sputc(194);sputc(220);
  sputc(170);sputc(166);sputc(132);sputc(84);sputc(26); //set comm open *SanUSB* (set comm open <string-sent-to-uart-when-tcp-port-opened>)
  
  //flash arduino led
  delay (500); 
  led = !led; 
  digitalWrite(13, led);
  AT1 = 0;
  --i;

  //Set the Remote command for port opened
  sputc(225+i);sputc(202);sputc(232);sputc(64);sputc(198);sputc(222);
  sputc(218);sputc(218);sputc(64);sputc(228);sputc(202);sputc(218);
  sputc(222);sputc(232);sputc(202);sputc(64);sputc(60); 
  sputc(26); //set comm remote remote (set comm remote <string-sent-to-remote-tcp-client-when-tcp-port-opened>)
  
  //flash arduino led
  led = !led;
  digitalWrite(13, led);
  delay (500);
  led = !led;
  digitalWrite(13, led);
  AT1 = 0;
  --i;

  //set local port to 80
  sputc(226+i);sputc(202);sputc(232);sputc(64);sputc(210);sputc(224);
  sputc(64);sputc(216);sputc(222);sputc(198);sputc(194);sputc(216);
  sputc(64);sputc(112);sputc(96);sputc(26); //set ip local 80 (set ip localport 80)
    
  //flash arudino led
  delay (500);
  led= !led; 
  digitalWrite(13, led);
  AT1 = 0;
  --i;
*/

  //these were commented out
  --i;
  --i;
  --i;

  //use SAVE command-string
  sputc(227+i);sputc(194);sputc(236);sputc(202);sputc(26); //save

  //flash arduino led
  delay (1000); 
  led = !led; 
  digitalWrite(13, led);
  AT1 = 0;
  --i;

  //join the SSID
  sputc(210+i);sputc(222);sputc(210);sputc(220);sputc(64);swputc(IDnet[0]);
  swputc(IDnet[1]);swputc(IDnet[2]);swputc(IDnet[3]);swputc(IDnet[4]);swputc(IDnet[5]);
  swputc(IDnet[6]);swputc(IDnet[7]);swputc(IDnet[8]);swputc(IDnet[9]);swputc(IDnet[10]);
  swputc(IDnet[11]);swputc(IDnet[12]);swputc(IDnet[13]);swputc(IDnet[14]);swputc(IDnet[15]);
  swputc(IDnet[16]);swputc(IDnet[17]);sputc(26); //join IDnet
   
  //flash arduino led
  led = !led; 
  digitalWrite(13, led);
  delay (4000); 
  led = !led; 
  digitalWrite(13, led);
  
  //confirm
  while (Wifly.available()) {
    comando[n] = Wifly.read();
    if (comando[n] == 73) {
      AT1 = 1;
    } 
    ++n;
  }
  
  //if not successful, keep trying
  while (AT1 == 0){ 
    delay (4000);
    while (Wifly.available()) {
      comando[n] = Wifly.read();
      if (comando[n] == 73) {
        AT1 = 1;
      } 
      ++n;
    }
     
    sputc(211+i);sputc(222);sputc(210);sputc(220);sputc(64);swputc(IDnet[0]);
    swputc(IDnet[1]);swputc(IDnet[2]);swputc(IDnet[3]);swputc(IDnet[4]);swputc(IDnet[5]);
    swputc(IDnet[6]);swputc(IDnet[7]);swputc(IDnet[8]);swputc(IDnet[9]);swputc(IDnet[10]);
    swputc(IDnet[11]);swputc(IDnet[12]);swputc(IDnet[13]);swputc(IDnet[14]);swputc(IDnet[15]);
    swputc(IDnet[16]);swputc(IDnet[17]);sputc(26); //join IDnet
     
    led = !led; 
    digitalWrite(13, led);
  }
  n = 0;
  AT2 = 0;
  --i;

}
