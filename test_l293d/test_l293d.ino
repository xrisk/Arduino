void setup() {
  for (int i = 2; i <= 13; i++)
    pinMode(i, OUTPUT);
}

void loop() {

 digitalWrite(2, HIGH);
 digitalWrite(12, LOW);
 digitalWrite(11, HIGH);

 digitalWrite(13, HIGH);
 digitalWrite(9, HIGH);
 digitalWrite(10, LOW);


 digitalWrite(8, HIGH);
 digitalWrite(6, HIGH);
 digitalWrite(7, LOW);

  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
 

}
