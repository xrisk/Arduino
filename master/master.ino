#include <SoftwareSerial.h>

SoftwareSerial bt(10, 11);

const int bt_pin = 7;

void btWrite(String s) {
  while (true) {
    Serial.println("attempting to write " + s);
    bt.print(s);
    String ret;
    while (bt.available() > 0)
      ret += (char) bt.read();
    Serial.println("output: " + ret);
    if (ret[0] == 'O' && ret[1] == 'K')
      break;
    if (ret.indexOf("ERROR:(17)") != -1)
      break;
    if (s.indexOf("LINK") != -1)
      delay(5000);
    else
      delay(500);
  }
}

String slaves[] = {
  "2014,3,198034",
//  "2014,3,198234",
};

void writeHeaders() {
 
  btWrite("AT\r\n");
  btWrite("AT+RMAAD\r\n");
  btWrite("AT+CMODE=1\r\n");
  btWrite("AT+INIT\r\n");
}

String buf = "Hello world";

void setup() {
  Serial.begin(38400);
  bt.begin(38400);
  pinMode(bt_pin, OUTPUT);
}

void loop() {
 
//  while (bt.available() > 0) {
//    Serial.write(bt.read());
//  }
  
  for (String s : slaves) {
    digitalWrite(bt_pin, HIGH);
    delay(1000);
    writeHeaders();
    Serial.println("Attempting to pair with " + s);
    btWrite("AT+LINK=" + s + "\r\n", 5000);
    bt.print("%");
    bt.print(buf);
    bt.print("$");
    char c;
    while (bt.available()) {
      c = bt.read();
      Serial.println("received " + c);
      if (c == '~') {
        Serial.println("received end char from " + s);
      } else {
        buf += c;
      }
    }
    digitalWrite(bt_pin, LOW);
    delay(500); 
  }

}
