#include <Wire.h>

void setup() {
  Wire.begin(8);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
}


void loop() {
}


void requestEvent()
{

  int cnt = 0;
  while (Serial.available() > 0)
    Wire.write(Serial.read());

}

void receiveEvent(int r) {
  
  while (Wire.available())
  {
    char c = Wire.read();
    Serial.print(c);
  }

}

