constexpr int GRIPPER_VERT_EN = 3;
constexpr int GRIPPER_VERT_DIR1 = 2;
constexpr int GRIPPER_VERT_DIR2 = 4;

constexpr int GRIPPER_HORZ_EN = 6;
constexpr int GRIPPER_HORZ_DIR1 = 5;
constexpr int GRIPPER_HORZ_DIR2 = 7;

void setup() {
  pinMode(GRIPPER_VERT_EN, OUTPUT);
  pinMode(GRIPPER_VERT_DIR1, OUTPUT);
  pinMode(GRIPPER_VERT_DIR2, OUTPUT);

  pinMode(GRIPPER_HORZ_EN, OUTPUT);
  pinMode(GRIPPER_HORZ_DIR1, OUTPUT);
  pinMode(GRIPPER_HORZ_DIR2, OUTPUT);

  Serial.begin(9600);
}

void gripper_vert_stop() {
  digitalWrite(GRIPPER_VERT_EN, HIGH);
  digitalWrite(GRIPPER_VERT_DIR1, HIGH);
  digitalWrite(GRIPPER_VERT_DIR2, HIGH);
}

void gripper_horz_stop() {
  digitalWrite(GRIPPER_HORZ_EN, HIGH);
  digitalWrite(GRIPPER_HORZ_DIR1, HIGH);
  digitalWrite(GRIPPER_HORZ_DIR2, HIGH);
}

void gripper_up() {
  digitalWrite(GRIPPER_VERT_EN, HIGH);
  digitalWrite(GRIPPER_VERT_DIR1, HIGH);
  digitalWrite(GRIPPER_VERT_DIR2, LOW);
}

void gripper_down() {
  digitalWrite(GRIPPER_VERT_EN, HIGH);
  digitalWrite(GRIPPER_VERT_DIR1, LOW);
  digitalWrite(GRIPPER_VERT_DIR2, HIGH);
}

void gripper_open() {
  digitalWrite(GRIPPER_HORZ_EN, HIGH);
  digitalWrite(GRIPPER_HORZ_DIR1, HIGH);
  digitalWrite(GRIPPER_HORZ_DIR2, LOW);
}

void gripper_close() {
  Serial.println("closing");
  digitalWrite(GRIPPER_HORZ_EN, HIGH);
  digitalWrite(GRIPPER_HORZ_DIR1, LOW);
  digitalWrite(GRIPPER_HORZ_DIR2, HIGH);
}

void loop() {
  if (Serial.available()) {
    char ch = Serial.read();
    if (ch == 'o') {
      gripper_open();
    } else if (ch == 'c') {
      gripper_close();
    } else if (ch == 'u') {
      gripper_up();
    } else if (ch == 'd') {
      gripper_down();
    } else if (ch == 's') {
      gripper_vert_stop();
    } else if (ch == 'x') {
      gripper_horz_stop();
    }
  }

}
