#include "drive.h"
#include "Arduino.h"

void changeSpeed(wheel w, int qty) {
  switch (w) {
  case LEFT:
    cur_L_speed += qty;
    break;
  case RIGHT:
    cur_R_speed += qty;
    break;
  case BOTH:
    cur_L_speed += qty;
    cur_R_speed += qty;
  }
  if (cur_L_speed < 0)
    cur_L_speed = 0;
  else if (cur_L_speed > MAX_SPEED)
    cur_L_speed = MAX_SPEED;
  if (cur_R_speed < 0)
    cur_R_speed = 0;
  else if (cur_R_speed > MAX_SPEED)
    cur_R_speed = MAX_SPEED;
}

void setSpeed(wheel w, int sp) {
  switch (w) {
  case LEFT:
    cur_L_speed = sp;
    break;
  case RIGHT:
    cur_R_speed = sp;
    break;
  case BOTH:
    cur_L_speed = sp;
    cur_R_speed = sp;
  }
  if (cur_L_speed < 0)
    cur_L_speed = 0;
  else if (cur_L_speed > MAX_SPEED)
    cur_L_speed = MAX_SPEED;

  if (cur_R_speed < 0)
    cur_R_speed = 0;
  else if (cur_R_speed > MAX_SPEED)
    cur_R_speed = MAX_SPEED;
}

void start_L(bool back = false) {
  if (back) {
    digitalWrite(P1_L, LOW);
    digitalWrite(P2_L, HIGH);
  } else {
    digitalWrite(P1_L, HIGH);
    digitalWrite(P2_L, LOW);
  }
}

void start_R(bool back = false) {
  if (back) {
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
