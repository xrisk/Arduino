#include <SoftwareSerial.h>

SoftwareSerial swserial(10, 11);

void setup() {
  Serial.begin(9600);
  swserial.begin(9600);

}

void loop() {
  while (Serial.available() > 0)
    swserial.write(Serial.read());

  while (swserial.available() > 0)
    Serial.write(swserial.read());
}
