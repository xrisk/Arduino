#include <math.h>

int echo_pin = 11;
int trig_pin = 10;

void setup() {
  Serial.begin(9600);
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
}

void setBrightness(double b) {
  if (0 <= b && b <= 200) {
    int d = floor(1.275 * b);
    analogWrite(3, d);
  }
}

void loop() {
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2); 
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);

  unsigned long t = pulseIn(echo_pin, HIGH);
  double dist = (t/ 2) * (0.034);

  setBrightness(dist);

  Serial.println(String(dist) + " cm");

  delay(200);

}
