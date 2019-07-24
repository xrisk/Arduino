#include <PS2X_lib.h>
#include <SparkFun_MAG3110.h>

#include "bot.h"
#include "drive.h"

movstate last_movestate = STR;
movstate cur_movestate = STR;

int angle = 0;
int initial_angle = 0;
int diff = 0;

int cur_L_speed = 0;
int cur_R_speed = 0;

PS2X ps2x;
MAG3110 mag;

void getHeading() { angle = mag.readHeading(); }

void setPins() {
  pinMode(PWM_L, OUTPUT);
  pinMode(PWM_R, OUTPUT);
  pinMode(P1_L, OUTPUT);
  pinMode(P2_L, OUTPUT);
  pinMode(P1_R, OUTPUT);
  pinMode(P2_R, OUTPUT);
}

void correctDrift() {
    Serial.println("attempting to correct drift");
    Serial.println("initial_angle=" + String(initial_angle));
    Serial.println("current_angle=" + String(angle));
    if (fabs(angle - initial_angle) <= 0.0)
        return;
    if (((initial_angle - angle + 360) % 360) > 180) {
        Serial.println("attempting to turn right");
        diff = +3;
    } else {
        Serial.println("attempting to turn left");
        diff = -3;
    }
    Serial.println("===========");
}

void setup() {
   Serial.begin(57600);
   if (mag.initialize() != MAG3110_SUCCESS) {
     Serial.println("failed IMU setup");
     while (1)
       ;
   }
   mag.setOffset(MAG3110_X_AXIS, OFFSET_X);
   mag.setOffset(MAG3110_Y_AXIS, OFFSET_Y);
   mag.x_scale = SCALE_X;
   mag.y_scale = SCALE_Y;
   mag.calibrated = true;
   mag.start();
    stop_L();
    stop_R();

     delay(300); // wait for ps2
     int error = ps2x.config_gamepad(PS2_CLK, PS2_CMD,
                                 PS2_SEL, PS2_DAT,
                                 false, false);
     if (error != 0) {
         Serial.println("No controller found. Check wiring.");
         while (1);
     }

  last_movestate = STOP;
}

void loop() {
  movstate cur_movestate = STOP;
  angle = mag.readHeading();
  if (angle < 0) angle += 360;
  ps2x.read_gamepad(false, false);
  bool up = ps2x.Button(PSB_PAD_UP);
  bool down = ps2x.Button(PSB_PAD_DOWN);
  bool left = ps2x.Button(PSB_CIRCLE);
  bool right = ps2x.Button(PSB_SQUARE);
  if (!(up || down || left || right)) {
    stop_L();
    stop_R();
    cur_movestate = STOP;
  }
  if (up) {
    cur_movestate = STR;
    start_L();
    start_R();
  }
  if (down) {
    cur_movestate = STR;
    start_L(true);
    start_R(true);
  }
  if (ps2x.Button(PSB_TRIANGLE)) {
    changeSpeed(BOTH, +INC_SPEED);
  }
  if (ps2x.Button(PSB_CROSS)) {
    changeSpeed(BOTH, -INC_SPEED);
  }
  if (ps2x.Button(PSB_L1)) {
    Serial.println("l1 pressed");
    initial_angle = angle;
    Serial.println("initial_angle=" + String(initial_angle));
  }
  if (left) {
    turn_L();
    cur_movestate = TURN;
  }
  if (right) {
    turn_R();
    cur_movestate = TURN;
  }

  
  if (cur_movestate == STR) {
    correctDrift();
  }

  analogWrite(PWM_L, cur_L_speed);
  analogWrite(PWM_R, cur_R_speed + diff);
  last_movestate = cur_movestate;

  delay(20);

}

