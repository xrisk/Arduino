#include <EnableInterrupt.h>

constexpr int LEFT_DIR = 8;
constexpr int LEFT_POWER = 9;
constexpr int RIGHT_DIR = 12;
constexpr int RIGHT_POWER = 13;

constexpr int GRIPPER_VERT_EN = 3;
constexpr int GRIPPER_VERT_DIR1 = 2;
constexpr int GRIPPER_VERT_DIR2 = 4;

constexpr int GRIPPER_HORZ_EN = 6;
constexpr int GRIPPER_HORZ_DIR1 = 5;
constexpr int GRIPPER_HORZ_DIR2 = 7;


#define SERIAL_PORT_SPEED 9600
#define RC_NUM_CHANNELS 6

#define RC_CH1 0
#define RC_CH2 1
#define RC_CH3 2                                                          
#define RC_CH4 3
#define RC_CH5 4
#define RC_CH6 5

#define RC_CH1_INPUT A0
#define RC_CH2_INPUT A1
#define RC_CH3_INPUT A2
#define RC_CH4_INPUT A3
#define RC_CH5_INPUT A4
#define RC_CH6_INPUT A5

/*
    R1 --- R2
    |       |
    |       |
    |       |
    R1 --- R4
*/

int rc_values[RC_NUM_CHANNELS];
int rc_start[RC_NUM_CHANNELS];
volatile int rc_shared[RC_NUM_CHANNELS];

constexpr int RC_CH1_MEAN = 1500;
constexpr int RC_CH2_MEAN = 1450;

constexpr int RC_CH5_MEAN = 1500;
constexpr int RC_CH6_MEAN = 1500;

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
  digitalWrite(GRIPPER_HORZ_EN, HIGH);
  digitalWrite(GRIPPER_HORZ_DIR1, LOW);
  digitalWrite(GRIPPER_HORZ_DIR2, HIGH);
}

void fwd()
{
  Serial.println("fwd");
  digitalWrite(LEFT_DIR, HIGH);
  digitalWrite(LEFT_POWER, HIGH);
  digitalWrite(RIGHT_DIR, HIGH);
  digitalWrite(RIGHT_POWER, HIGH);
}

void rev()
{
  Serial.println("rev");
  digitalWrite(LEFT_DIR, LOW);
  digitalWrite(LEFT_POWER, HIGH);
  digitalWrite(RIGHT_DIR, LOW);
  digitalWrite(RIGHT_POWER, HIGH);
}

void left()
{
     Serial.println("left");
    digitalWrite(LEFT_DIR, HIGH);
    digitalWrite(LEFT_POWER, HIGH);
    digitalWrite(RIGHT_DIR, LOW);
    digitalWrite(RIGHT_POWER, HIGH);
}
void right()
{
     Serial.println("right");
    digitalWrite(LEFT_DIR, LOW);
    digitalWrite(LEFT_POWER, HIGH);
    digitalWrite(RIGHT_DIR, HIGH);
    digitalWrite(RIGHT_POWER, HIGH);
}

void stop()
{
  Serial.println("stop");
  digitalWrite(LEFT_POWER, LOW);
  digitalWrite(RIGHT_POWER, LOW);
}

void setup()
{
  pinMode(LEFT_DIR, OUTPUT);
  pinMode(LEFT_POWER, OUTPUT);
  pinMode(RIGHT_DIR, OUTPUT);
  pinMode(RIGHT_POWER, OUTPUT);


  pinMode(GRIPPER_VERT_EN, OUTPUT);
  pinMode(GRIPPER_VERT_DIR1, OUTPUT);
  pinMode(GRIPPER_VERT_DIR2, OUTPUT);

  pinMode(GRIPPER_HORZ_EN, OUTPUT);
  pinMode(GRIPPER_HORZ_DIR1, OUTPUT);
  pinMode(GRIPPER_HORZ_DIR2, OUTPUT);

  pinMode(RC_CH1_INPUT, INPUT);
  pinMode(RC_CH2_INPUT, INPUT);
  pinMode(RC_CH3_INPUT, INPUT);
  pinMode(RC_CH4_INPUT, INPUT);
  pinMode(RC_CH5_INPUT, INPUT);
  pinMode(RC_CH6_INPUT, INPUT);

  enableInterrupt(RC_CH1_INPUT, calc_ch1, CHANGE);
  enableInterrupt(RC_CH2_INPUT, calc_ch2, CHANGE);
  enableInterrupt(RC_CH3_INPUT, calc_ch3, CHANGE);
  enableInterrupt(RC_CH4_INPUT, calc_ch4, CHANGE);
  enableInterrupt(RC_CH5_INPUT, calc_ch5, CHANGE);
  enableInterrupt(RC_CH6_INPUT, calc_ch6, CHANGE);

  Serial.begin(9600);
}

void calc_input(uint8_t channel, uint8_t input_pin)
{
  if (digitalRead(input_pin) == HIGH)
  {
    rc_start[channel] = micros();
  }
  else
  {
    int rc_compare = (int)(micros() - rc_start[channel]);
    rc_shared[channel] = rc_compare;
  }
}

void rc_read_values()
{
  noInterrupts();
  memcpy(rc_values, (const void *)rc_shared, sizeof(rc_shared));
  interrupts();
}

void calc_ch1() {
  calc_input(RC_CH1, RC_CH1_INPUT);
}
void calc_ch2() {
  calc_input(RC_CH2, RC_CH2_INPUT);
}
void calc_ch3() {
  calc_input(RC_CH3, RC_CH3_INPUT);
}
void calc_ch4() {
  calc_input(RC_CH4, RC_CH4_INPUT);
}
void calc_ch5() {
  calc_input(RC_CH5, RC_CH5_INPUT);
}
void calc_ch6() {
  calc_input(RC_CH6, RC_CH6_INPUT);
}

void loop()
{

  rc_read_values();

  if (abs(rc_values[RC_CH6] - RC_CH6_MEAN) <= 200)
    gripper_vert_stop();
  else if (rc_values[RC_CH6] < RC_CH6_MEAN)
    gripper_up();
  else
    gripper_down();

  if (abs(rc_values[RC_CH5] - RC_CH5_MEAN) <= 200)
    gripper_horz_stop();
  else if (rc_values[RC_CH5] < RC_CH5_MEAN)
    gripper_open();
  else
    gripper_close();

  if (abs(rc_values[RC_CH2] - RC_CH2_MEAN) >= 100)
  {
    if (rc_values[RC_CH2] > RC_CH2_MEAN)
      fwd();
    else
      rev();
  }

  else if (abs(rc_values[RC_CH1] - RC_CH1_MEAN) >= 100)
  {
    if (rc_values[RC_CH1] > RC_CH1_MEAN)
      left();
    else
      right();
  }

  else
    stop();

  delay(100);
}

