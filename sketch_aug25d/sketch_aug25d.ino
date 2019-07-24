constexpr int M1_EN = 2;
constexpr int M1_DIR1 = 3;
constexpr int M1_DIR2 = 4;

constexpr int M2_EN = 6;
 constexpr int M2_DIR1 = 7;
constexpr int M2_DIR2 = 8;



void setup() {
  pinMode(M1_EN, OUTPUT);
  pinMode(M1_DIR1, OUTPUT);
  pinMode(M1_DIR2, OUTPUT);

  pinMode(M2_EN, OUTPUT);
  pinMode(M2_DIR1, OUTPUT);
  pinMode(M2_DIR2, OUTPUT);

  Serial.begin(9600);
}

void stop() {
  digitalWrite(M1_EN, HIGH);
  digitalWrite(M1_DIR1, HIGH);
  digitalWrite(M1_DIR2, HIGH);

  digitalWrite(M2_EN, HIGH);
  digitalWrite(M2_DIR1, HIGH);
  digitalWrite(M2_DIR2, HIGH);
}

void up() {
  digitalWrite(M1_EN, HIGH);
  digitalWrite(M1_DIR1, HIGH);
  digitalWrite(M1_DIR2, LOW);
}

void down() {
  digitalWrite(M1_EN, HIGH);
  digitalWrite(M1_DIR1, LOW);
  digitalWrite(M1_DIR2, HIGH);
}

void fwd() {
  digitalWrite(M2_EN, HIGH);
  digitalWrite(M2_DIR1, HIGH);
  digitalWrite(M2_DIR2, LOW);
}

void back() {
  digitalWrite(M2_EN, HIGH);
  digitalWrite(M2_DIR1, LOW);
  digitalWrite(M2_DIR2, HIGH);
}

void loop() {

  if (Serial.available()) {
    char ch = Serial.read();
    if (ch == 'f')
      fwd();
    else if (ch == 'b')
      back();
    else if (ch == 'u')
      up();
    else if (ch == 'd')
      down();
    else
      stop();
  }

}

