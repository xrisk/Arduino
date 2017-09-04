#include <stdbool.h>


int enable_yz = 3;
int enable_x = 10;

int y1 = 6;
int y2 = 7;

int z1 = 5;
int z2 = 4;

int x1 = 9;
int x2 = 8;

void mov_y(int dir, int time=50) {
  digitalWrite(enable_yz, HIGH);
  if (dir == 1) {
    digitalWrite(y1, HIGH);
    digitalWrite(y2, LOW);
  } else {
    digitalWrite(y1, LOW);
    digitalWrite(y2, HIGH);
  }
  int cur_time = millis();
  while ((millis() - cur_time) < time) {}
  digitalWrite(enable_yz, LOW);
}

void mov_z(int dir, int time=500) {
  digitalWrite(enable_yz, HIGH);
  if (dir == 1) { 
    digitalWrite(z1, HIGH);
    digitalWrite(z2, LOW);
  } else {
    digitalWrite(z1, LOW);
    digitalWrite(z2, HIGH);
  }
  int cur_time = millis();
  while ((millis() - cur_time) < time) {}
  digitalWrite(enable_yz, LOW);
}

void mov_x(int dir, int time=500) {
  digitalWrite(enable_x, HIGH);
  if (dir == 1) { 
    digitalWrite(x1, HIGH);
    digitalWrite(x2, LOW);
  } else {
    digitalWrite(x1, LOW);
    digitalWrite(x2, HIGH);
  }
  int cur_time = millis();
  while ((millis() - cur_time) < time) {}
  digitalWrite(enable_x, LOW);
}


void setup() {
  pinMode(y1, OUTPUT);
  pinMode(y2, OUTPUT);
  pinMode(z1, OUTPUT);
  pinMode(z1, OUTPUT);
  pinMode(x1, OUTPUT);
  pinMode(x2, OUTPUT);
 
  mov_x(1 , 500);
  mov_y(1, 500);
//  mov_z(1, 1000);
}





void loop() {


}
