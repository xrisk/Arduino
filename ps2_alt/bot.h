#ifndef BOT_H

#define BOT_H

#define PS2_DAT 8 // orange
#define PS2_CMD 9 // red
#define PS2_CLK 10 // green
#define PS2_SEL 11 // yellow

#define PWM_R  46
#define PWM_L  44
#define P1_L  40
#define P2_L  42
#define P1_R  36
#define P2_R  38

#define MAX_SPEED 50
#define INC_SPEED 5

#define OFFSET_X -722
#define OFFSET_Y 19
#define SCALE_X 0.0008
#define SCALE_Y 0.0012

enum wheel { LEFT, RIGHT, BOTH };
enum movstate { STOP, STR, TURN };
enum lstate { LO, HI };

extern int cur_L_speed;
extern int cur_R_speed;
extern int angle;

#endif

