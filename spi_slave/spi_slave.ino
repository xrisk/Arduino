int cur_byte = 0;

int clock_pin = 2;
int miso_pin = 3;
int mosi_pin = 4;

String message = "Hello world from slave!";
int idx = 0;

void setup() {
  Serial.begin(9600);
  pinMode(clock_pin, INPUT);
  pinMode(miso_pin, OUTPUT);
  pinMode(mosi_pin, INPUT);
}

int transferBit(int b) {
  int ret = 0;
  int clk = digitalRead(clock_pin);
  while (clk == LOW) {} 
  ret = digitalRead(mosi_pin);
  digitalWrite(miso_pin, b);
  while (clk == HIGH) {} 
  return ret;
}

char transferChar(char b) {
  char ret;
  for (int i = 0; i < 8; i++) {
    ret = ret * 2 + transferBit((b & (1<<i)) > 0);
  }
  return ret;
}

void loop() {
   Serial.println(transferChar(message[idx++]));
   if (idx >= message.length()) idx = 0;
}
