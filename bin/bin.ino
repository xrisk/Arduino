const int p1 = 11;
const int p2 = 6;
const int p3 = 12;
const int p4 = 13;

int lo = 0;
int hi = 500;

void setup() {
  pinMode(p1, OUTPUT);
  pinMode(p2, OUTPUT);
  pinMode(p3, OUTPUT);
  pinMode(p4, OUTPUT);

  Serial.begin(9600);
}

void turn() {
  digitalWrite(p1, HIGH);
  digitalWrite(p2, LOW);
  digitalWrite(p3, LOW);
  digitalWrite(p4, HIGH);
}

void stop() {
  digitalWrite(p1, LOW);
  digitalWrite(p2, LOW);
  digitalWrite(p3, LOW);
  digitalWrite(p4, LOW);
}

void loop() {
  int mid = (lo + hi) / 2;
  Serial.print("Next `delay` value: ");
  Serial.println(mid);

  Serial.println("Place the bot at starting position and press s");
  while (true) {
    if (Serial.available()) {
      char ch = Serial.read();
      if (ch == 's') break;
    }
  }

  turn();
  delay(mid);
  stop();

  Serial.println("Press g to increase the delay or l to decrease the delay...");
  while (!Serial.available())
    ;
  char ch = Serial.read();

  if (ch == 'g')
    lo = mid;
  else
    hi = mid;
}
