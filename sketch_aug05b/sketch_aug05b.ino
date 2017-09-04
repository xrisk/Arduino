int led_pin = 13;
int cur = 128;

void setup() {
  pinMode(led_pin, OUTPUT);  
}

void loop() {
  analogWrite(led_pin, (cur = (cur + 128) % 256));
  delay(200);
}
