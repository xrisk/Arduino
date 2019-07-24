#include <SoftwareSerial.h>

int tx = 5;
int rx = 4;
int key_pin = 3;

SoftwareSerial swserial(tx, rx);

void setup() {
    Serial.begin(9600);
    swserial.begin(9600);
    pinMode(key_pin, OUTPUT);
    digitalWrite(key_pin, HIGH);

    swserial.write("AT");
    delay(200);
//    swserial.write("AT+VERSION?");
}

void loop() {

 
    while (swserial.available() > 0) 
	    Serial.write(swserial.read());
     
    while (Serial.available() > 0)
	swserial.write(Serial.read());
  
}

