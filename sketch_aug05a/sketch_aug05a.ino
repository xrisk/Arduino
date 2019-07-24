int led_pin = 13;
int cur = HIGH;

int lastEventMillis = 0;

void setup() {
  pinMode(led_pin, OUTPUT); 
}

void loop() {
  int currentMillis = millis();
  if (currentMillis - lastEventMillis >= 50) {
    digitalWrite(led_pin, (cur = cur^= 1));
    lastEventMillis = currentMillis;
  }
  
}
