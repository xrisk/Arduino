void setup() {


 pinMode(8, OUTPUT);
 pinMode(9, OUTPUT);
 digitalWrite(8, HIGH);
 digitalWrite(9, LOW);

 pinMode(13, OUTPUT);
 pinMode(12, OUTPUT);

 digitalWrite(12, HIGH);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  for (int i = 0; i <= 255; i+=20) {
    analogWrite(13, i);
    Serial.println(i);
    delay(50);
  }

}
