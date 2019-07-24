int x1 = 9;
int x2 = 10;

void setup() {
  pinMode(x1, OUTPUT);
  pinMode(x2, OUTPUT);
pinMode(3, OUTPUT);
}

void loop() {
  digitalWrite(x1, LOW);
  digitalWrite(x2, HIGH);
 analogWrite(3, 0);
}
