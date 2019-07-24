#include <PS2X_lib.h>  
#include <DebugMacros.h>
#include <LSM303CTypes.h>
#include <SparkFunIMU.h>
#include <SparkFunLSM303C.h>
#include <SoftwareSerial.h>
#include <PID_v1.h>

#define PS2_DAT 8 // orange
#define PS2_CMD 9 // red
#define PS2_CLK 10 // green
#define PS2_SEL 11 // yellow

#define PWM_L  44
#define PWM_R  46
#define P1_L  40
#define P2_L  42
#define P1_R  36
#define P2_R  38

#define MAX_SPEED 50

enum wheel { LEFT, RIGHT, BOTH };
enum movstate { STOP, STR, TURN };
enum lstate { LO, HI };

int cur_L_speed;
int cur_R_speed;

float mag_x[10];
float mag_y[10];

int idx;
float sens_x;
float sens_y;
double angle;
double initial_angle;
double wheel_ratio = 1.0d;

int inc_speed = 5;

movstate last_movestate = STR;
movstate cur_movestate = STR;


PS2X ps2x; // create PS2 Controller Class
LSM303C imu;

PID pid = PID(&angle , &wheel_ratio, &initial_angle, 2, 5, 1, DIRECT);


 void init_rolling_average() {
     float sum_x = 0, sum_y = 0;
     for (int i = 0; i < 10; i++) {
         mag_x[i] = imu.readMagX();
         mag_y[i] = imu.readMagY();
         delay(5);
         sum_x += mag_x[i];
         sum_y += mag_y[i];
     }
     sens_x = sum_x / 10.0f;
     sens_y = sum_y / 10.0f;

     angle = atan2(sens_y, sens_x) * 180.0f / M_PI;
     if (angle < 0) angle += 360;
 }

// void update_rolling_average() {
//     float sum_x = sens_x * 10.0f;
//     float sum_y = sens_y * 10.0f;
//
//     sum_x -= mag_x[idx];
//     sum_y -= mag_y[idx];
//
//     mag_x[idx] = imu.readMagX();
//     mag_y[idx] = imu.readMagY();
//
//     sum_x += mag_x[idx];
//     sum_y += mag_x[idx];
//
//     idx++; if (idx == 10) idx = 0;
//
//     sens_x = sum_x / 10.0f;
//     sens_y = sum_y / 10.0f;
//
//
//     angle = atan2(sens_y, sens_x) * 180.0f / M_PI;
//     if (angle < 0) angle += 360;
// }

 void correct_drift() {
    Serial.println("correcting drift");
     Serial.println(initial_angle);
     Serial.println(angle);
     double old_ratio = wheel_ratio;
     Serial.println(wheel_ratio);
     pid.Compute();
     if (wheel_ratio > 0 && wheel_ratio < 2) {
//       Serial.println(old_ratio);
//       Serial.println(wheel_ratio);
       float f = wheel_ratio * cur_L_speed;
       setSpeed(RIGHT, f);
     }
     else
      wheel_ratio = old_ratio;
 }

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
    if (cur_L_speed < 0) cur_L_speed = 0;
    else if (cur_L_speed > MAX_SPEED) cur_L_speed = MAX_SPEED;
    //
    if (cur_R_speed < 0) cur_R_speed = 0;
    else if (cur_R_speed > MAX_SPEED) cur_R_speed = MAX_SPEED;
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
  if (cur_L_speed < 0) cur_L_speed = 0;
  else if (cur_L_speed > MAX_SPEED) cur_L_speed = MAX_SPEED;

  if (cur_R_speed < 0) cur_R_speed = 0;
  else if (cur_R_speed > MAX_SPEED) cur_R_speed = MAX_SPEED;
}



void start_R(bool fwd=false) {
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

void setup() {

    stop_L();
    stop_R();

    Serial.begin(57600);

     if (imu.begin() != IMU_SUCCESS) {
         Serial.println("Failed IMU setup.");
         while (1);
     }

    delay(300); // wait for ps2

    int error = ps2x.config_gamepad(PS2_CLK, PS2_CMD,
                                PS2_SEL, PS2_DAT,
                                false, false);

    if (error != 0) {
        Serial.println("No controller found. Check wiring.");
        while (1);
    }

    pinMode(PWM_L, OUTPUT);
    pinMode(PWM_R, OUTPUT);
    pinMode(P1_L, OUTPUT);
    pinMode(P2_L, OUTPUT);
    pinMode(P1_R, OUTPUT);
    pinMode(P2_R, OUTPUT);

     last_movestate = STOP;
     init_rolling_average();
     initial_angle = angle;

     pid.SetMode(AUTOMATIC);


}




void loop() {

   movstate cur_movestate = STOP;

    ps2x.read_gamepad(false, false); 
    
    bool up = ps2x.Button(PSB_PAD_UP);
    bool down = ps2x.Button(PSB_PAD_DOWN);
    bool left = ps2x.Button(PSB_CIRCLE);
    bool right = ps2x.Button(PSB_SQUARE);

    if (!(up || down || left || right)) {
        stop_L();
        stop_R();
        cur_movestate = STOP;
//        Serial.println("stopping bot because no buttons pressed");
    }     

    if (up) {  
//      Serial.println("starting forward movement");
        cur_movestate = STR;
        start_L();
        start_R();
    }

    if (down) {
        Serial.println("starting reverse movement");
        cur_movestate = STR;
        start_L(true);
        start_R(true); 
    }   

     if (ps2x.Button(PSB_TRIANGLE)) {
        changeSpeed(BOTH, +inc_speed);
    }

    if (ps2x.Button(PSB_CROSS)) {
        changeSpeed(BOTH, -inc_speed);
    }

    if (left) {
//        cMhangeSpeed(BOTH, 
        turn_L();
        cur_movestate = TURN;
    }

    if (right) {
        turn_R();                        
        cur_movestate = TURN;
    }
    
    init_rolling_average();
    if ((cur_movestate == STR || cur_movestate == STOP) && last_movestate == TURN) {
      initial_angle = angle;
    } else if (cur_movestate == STR && (last_movestate == STR || last_movestate == STOP)) {
      correct_drift();
    }

//    Serial.println(cur_L_speed);
//    Serial.println(cur_R_speed);
    analogWrite(PWM_L, cur_L_speed);
    analogWrite(PWM_R, cur_R_speed);

    last_movestate = cur_movestate;

//    Serial.println("angle " + String(angle));
//    Serial.println("lspeed" + String(cur_L_speed));
//    Serial.println("rspeed" + String(cur_R_speed));

    delay(20);
}
