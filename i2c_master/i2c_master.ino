#include <Wire.h>

void setup()
{
  Wire.begin();
  Serial.begin(9600);
}

int slave = 8;

void loop() {
  if (Serial.available()) {
    Wire.beginTransmission(8);
    while (Serial.available() > 0) {
      char ch = Serial.read();
      Wire.write(ch);
    }
     Wire.endTransmission();
  }

  Wire.requestFrom(8, 10);
  while (Wire.available() > 0) {
    char c = Wire.read();
    if (isPrintable(c))
      Serial.print(c);
  }


  
}

