void start_L(bool fwd = false) {
  if (fwd) {
    digitalWrite(P1_L, LOW);
    digitalWrite(P2_L, HIGH);
  } else {
    digitalWrite(P1_L, HIGH);
    digitalWrite(P2_L, LOW);
  }
}

void start_R(bool fwd = false) {
  if (fwd) {
    digitalWrite(P1_R, LOW);
    digitalWrite(P2_R, HIGH);
  } else {
    digitalWrite(P1_R, HIGH);
    digitalWrite(P2_R, LOW);
  }
}

void stop_L() {
  digitalWrite(P1_L, LOW);
  digitalWrite(P2_L, LOW);
}

void stop_R() {
  digitalWrite(P1_R, LOW);
  digitalWrite(P2_R, LOW);
}

void turn_L() {
  start_L();
  start_R(true);
}

void turn_R() {
  start_R();
  start_L(true);
}

