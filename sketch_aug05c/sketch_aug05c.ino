int led_pin = 13;
int cur = HIGH;
int f =  1;

void setup() {
  pinMode(led_pin, OUTPUT);  
}

void loop() {
  if (f == 1) {
    digitalWrite(led_pin, HIGH);
    f = 0;
  }
 
}
