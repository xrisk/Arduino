
void setup() {
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  analogWrite(11, 20);

}

void loop() {

  
  if (Serial.available()) {
    String f = Serial.readString();
    Serial.println(f);
    if (f == "fwd") {
      Serial.println("trigger");
      digitalWrite(13, HIGH);
      digitalWrite(12, LOW);
    } else if (f == "rev") {
       digitalWrite(12, HIGH);
      digitalWrite(13, LOW);
    } else if (f == "sb") {
       digitalWrite(12, HIGH);
      digitalWrite(13, HIGH);
    } else if (f == "nb") {
       digitalWrite(12, LOW);
      digitalWrite(13, LOW);
    } else if (isdigit(f[0])) {
      f.trim();
      analogWrite(11, f.toInt());
    }
  }


    

}
