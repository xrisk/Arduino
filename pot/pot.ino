#include <Servo.h>

constexpr int SERVO_PIN = 8;

Servo serv;

void setup() {
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);
  
  Serial.begin(9600);
  serv.attach(SERVO_PIN);
}

void loop() {
  int read = analogRead(A0);
  int val = constrain(map(read, 0, 256, 0, 180), 0, 180);
  serv.write(val);
  Serial.print(read);
  Serial.print(" ");
  Serial.println(val);
  delay(15);
}
