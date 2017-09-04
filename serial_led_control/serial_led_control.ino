const int led_pin = 13;

void setup() {
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
}

String buf;

void loop() {
  while (Serial.available() > 0)
  {
    buf = Serial.readStringUntil('\n');
    Serial.println(buf);
    if (buf == "ON")
      digitalWrite(led_pin, HIGH);
    else if (buf == "OFF")
      digitalWrite(led_pin, LOW);
  }

}
