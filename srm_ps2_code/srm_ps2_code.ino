/*
===============================================================================
                  Developed by SRM Tech Team Robocon
                          Coding Domain 2015
                        # CODE FOR MEGA ONLY #
===============================================================================
                     This code test PS2 controller
The connections should correspond to the variable in the PS2 SETUP PART. The PS2 
has to be powered externally.#contact electronics domain for further details#.
===============================================================================
HOW TO USE
PS2_DAT => ORANGE
PS2_CLK => GREEN
PS2_CMD => RED
PS2_SEL => YELLOW
BROWN   => VCC (3.3V)
BLACK   => GND

*/
#include<PS2X_lib.h>
//=============================================================================
int pins[4] = {8, 9, 10, 11};
//#include<Wire.h>
int CLOCK = pins[0];
          int COMMAND = pins[1];
         int  ATTENTION = pins[3];
      int DATA = pins[2];
#define BAUD_RATE 115200
//=============================================================================
PS2X ps2x;
boolean up=0;
boolean down=0;

boolean left=0;
boolean right=0;

boolean triangle=0;
boolean sqr=0;
boolean cross=0;
boolean circle=0;

boolean r1=0;
boolean r2=0, p_r2=0;

boolean l1=0;
boolean l2=0, p_l2=0;
boolean r3=0;
boolean l3=0;

int RY=0;
int RX=0;

int LY=0;
int LX=0;
int d=0;
boolean start=0;
boolean select=0;

boolean start_flag=0;

void readButtons();// to check the value of PS2 buttons
void printState(); // to print/read the value of PS2 buttons
void setup()
{
  ps2x.config_gamepad(CLOCK,COMMAND,ATTENTION,DATA);   // (clock(blue),command(orange), attention(yellow), data(brown))
  Serial.begin(BAUD_RATE);
}

void loop()
{
  readButtons();
  printState();
}

void readButtons()
{
  ps2x.read_gamepad();
  up=ps2x.Button(PSB_PAD_UP);
  down=ps2x.Button(PSB_PAD_DOWN);
  left=ps2x.Button(PSB_PAD_LEFT);
  right=ps2x.Button(PSB_PAD_RIGHT);

  triangle=ps2x.Button(PSB_GREEN);
  circle=ps2x.Button(PSB_RED);
  cross=ps2x.Button(PSB_BLUE);
  sqr=ps2x.Button(PSB_PINK);

  r1=ps2x.Button(PSB_R1);
  r2=ps2x.Button(PSB_R2);
  l1=ps2x.Button(PSB_L1);
  l2=ps2x.Button(PSB_L2);

  r3=ps2x.Button(PSB_R3);
  l3=ps2x.Button(PSB_L3);

  RY=ps2x.Analog(PSS_RY);
  RX=ps2x.Analog(PSS_RX);

  LY=ps2x.Analog(PSS_LY);
  LX=ps2x.Analog(PSS_LX);

  start=ps2x.Button(PSB_START);
  select=ps2x.Button(PSB_SELECT);PS2_DAT => ORANGE
PS2_CLK => GREEN
PS2_CMD => RED
PS2_SEL => YELLOW
BROWN   => VCC (3.3V)
BLACK   => GND

}

void printState()
{
  Serial.print(up);
  Serial.print(" ");
  Serial.print(down);
  Serial.print(" ");
  Serial.print(" ");
  Serial.print(left);
  Serial.print(" ");
  Serial.print(right);
  Serial.print(" ");

  Serial.print(triangle);
  Serial.print(" ");
  Serial.print(circle);
  Serial.print(" ");
  Serial.print(cross);
  Serial.print(" ");
  Serial.print(sqr);
  Serial.print(" ");

  Serial.print(r1);
  Serial.print(" ");
  Serial.print(r2);
  Serial.print(" ");
  Serial.print(" ");
  Serial.print(l1);
  Serial.print(" ");
  Serial.print(l2);
  Serial.print(" ");
  Serial.print(r3);
  Serial.print(" ");
  Serial.print(l3);
  Serial.print(" ");

  Serial.print(RY);
  Serial.print(" ");
  Serial.print(RX);
  Serial.print(" ");
  Serial.print(LY);
  Serial.print(" ");
  Serial.print(LX);
  Serial.print(" ");

  Serial.print(start);
  Serial.print(" ");
  Serial.println(select);
  delay(10);
}
