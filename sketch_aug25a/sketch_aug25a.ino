#define PWM_R  46
#define PWM_L  44
#define P1_L  40
#define P2_L  42
#define P1_R  36
#define P2_R  38

void setup() {
  pinMode(PWM_R, OUTPUT);
  pinMode(PWM_L, OUTPUT);
  pinMode(P1_L, OUTPUT);
  pinMode(P2_L, OUTPUT);
  pinMode(P1_R, OUTPUT);
  pinMode(P2_R, OUTPUT);

}

void loop() {
analogWrite(PWM_R,20);
analogWrite(PWM_L, 20);
digitalWrite(P1_L, HIGH);
digitalWrite(P2_L, LOW);
  digitalWrite(P1_R, HIGH);
  digitalWrite(P2_R, LOW);

}
