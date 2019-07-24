int led_pin = 13;
int t = 0;
int inc = 5;

void setup() {
  pinMode(led_pin, OUTPUT);
  Serial.begin(9600);
}



void loop() {
  long on = t * (10000);
  long off = 1000000 - on;
  digitalWrite(led_pin, HIGH);
  delayMicroseconds(on);
  digitalWrite(led_pin, LOW);
  delayMicroseconds(off);
  if (t + inc > 100 || t + inc < 0) {
    inc = -inc;
  }
    t += inc;
  
  Serial.println(on);
  Serial.println(off);
}
