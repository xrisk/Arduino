#include <Wire.h>

void setup() {
  Wire.begin(8);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
}


void loop() {
//  while (Wire.available() > 0)
//    Serial.write(Wire.read());

}

void requestEvent()
{
  while (Serial.available() > 0) {
    Wire.write(Serial.read());
  }
//  Wire.flush();
}

void receiveEvent(int t) {
  while (Wire.available())
  {
    char c = Wire.read();
    Serial.print(c);
  }

}

