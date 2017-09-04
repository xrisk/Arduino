#include <SoftwareSerial.h>

const char BEGIN = '%';
const char SEP = '$';
const char END = '~';
SoftwareSerial bt(10, 11);

const int bt_pin = 8;

void setup() { 
  Serial.begin(38400);
  bt.begin(38400);

  pinMode(bt_pin, OUTPUT);
  digitalWrite(bt_pin, HIGH);
}

String buf = "";

void loop() {
  char c;
  
  if (bt.available()) {
    c = bt.read();
    
    if (c == BEGIN) { // master-slave connection established
      // master will send its version of buf and then send SEP
      while ((c = bt.read()) != SEP) { 
        buf += c;
      }

       // TODO: properly parse buf
       Serial.println(buf);
       
       // now send whatever we have from the user
       while (Serial.available() > 0) {
        bt.write(Serial.read());
       }
        
       bt.write(END); // indicate end of transmission

       // cycle power on bt chip
       digitalWrite(8, LOW);
       delay(500);
       digitalWrite(8, HIGH);
    }
  }
  
}
