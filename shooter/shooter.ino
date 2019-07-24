#include <Servo.h>
#include <limits.h>

Servo serv;

constexpr int SERVO_PIN = 9;
constexpr int SWITCH_PIN = 2;



unsigned long volatile last_debounce_time = ULONG_MAX;
unsigned long volatile lock = 0;
int initial_state;


void debounce() {

  Serial.println("debounce");

  if (lock == 0) {

    lock = 1;

    unsigned long cur_time = millis();

    if (last_debounce_time == ULONG_MAX || (cur_time - last_debounce_time >=  50)) {
      passBall();
    }
    last_debounce_time = cur_time;

    lock = 0;

  }

}

void passBall() {
  Serial.println("toggled");
  interrupts();

  serv.write(90);
  delay(800);
  serv.write(15);
}

void setup() {
  Serial.begin(9600);
  interrupts();
  serv.attach(SERVO_PIN);

  serv.write(15);

  pinMode(SWITCH_PIN, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(SWITCH_PIN), debounce, CHANGE);

}




void loop() {
  Serial.println(digitalRead(SWITCH_PIN));
  delay(100);
}
