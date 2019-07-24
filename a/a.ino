
const byte interruptPin = 8;
volatile byte state = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);
}

void loop() {
  Serial.println(digitalRead(8));
  digitalWrite(LED_BUILTIN, state);
}

void blink() {
  Serial.println("blink");
  state = !state;
}
