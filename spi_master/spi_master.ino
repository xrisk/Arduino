int clock_pin = 2;
int miso_pin = 3;
int mosi_pin = 4;
int cur_byte = 1;

String message = "Hello world from master!";
int idx = 0;

void setup() {
  Serial.begin(9600);
  pinMode(clock_pin, OUTPUT);
  pinMode(miso_pin, INPUT);
  pinMode(mosi_pin, OUTPUT);
}

char transferChar(char c) {
  char in = 0;
  for (int i = 0; i < 8; i++) {
    digitalWrite(mosi_pin, (c & (1 << i) > 0));
    digitalWrite(clock_pin, HIGH);
    delay(500);
    in = in * 2 + digitalRead(miso_pin);
    digitalWrite(clock_pin, LOW);
    delay(500);
  }
  return in;
}

void loop() {
  Serial.println(transferChar(message[idx++]));
  if (idx >= message.length()) idx = 0;
}

