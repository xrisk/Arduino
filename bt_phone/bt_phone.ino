#include <SoftwareSerial.h>

SoftwareSerial bt(10, 11);

void setup() {
  Serial.begin(9600);
  bt.begin(38400);

}

void loop() {
  while (Serial.available() > 0) {
    bt.write(Serial.read());
  }

  while (bt.available() > 0) {
    Serial.write(bt.read());
  }
  
}
