#include <IRremote.h>
const unsigned int IR_RECEIVER_PIN = 11; 
const unsigned int BAUD_RATE = 9600;

IRrecv ir_receiver(IR_RECEIVER_PIN); 
decode_results results;

void setup() { 
  Serial.begin(BAUD_RATE); 
  ir_receiver.enableIRIn();
}

void dump(const decode_results* results) { 
  const int protocol = results->decode_type; 
  switch (protocol) {
    case UNKNOWN: Serial.println("not recognized.");
      break;
    case NEC: Serial.println("NEC");
      break;
    case SONY: Serial.println("SONY");
      break;
    case RC5: Serial.println("RC5");
      break;
    case RC6: Serial.println("RC6");
      break;
    default: Serial.println("really unknown");
  }
  Serial.print("Value: "); 
  Serial.print(results->value, HEX);
  Serial.print(" ("); 
  Serial.print(results->bits, DEC); 
  Serial.println(" bits)");
}

void loop() { 
  if (ir_receiver.decode(&results)) {
    dump(&results); 
    ir_receiver.resume();
  } 
}
