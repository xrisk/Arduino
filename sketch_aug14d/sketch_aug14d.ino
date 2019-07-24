#include <SoftwareSerial.h>

SoftwareSerial bt(10, 11);

void btwrite(String s) {
  bt.print(s);
  delay(200);
}

void setup() {
  Serial.begin(9600);
  bt.begin(38400);

  btwrite("AT\r\n");
  btwrite("AT\r\n");
  btwrite("AT+VERSION\r\n");
 
}

void loop() {
//  while (Serial.available() > 0)
//    bt.write(Serial.read());

  while (bt.available() > 0)
    Serial.write(bt.read());
}
