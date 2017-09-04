int b = 0;
int inc = 5;

void setup() {
  pinMode(3, OUTPUT);
  pinMode(13, OUTPUT);
  
}

void loop() {
  analogWrite(3, b);
  b += inc;
  if (b < 0 || b > 255)
    inc = -inc;
  delay(5);

}
