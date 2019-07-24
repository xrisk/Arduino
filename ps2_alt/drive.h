#include "bot.h"

#ifndef DRIVE_H

#define DRIVE_H

void changeSpeed(wheel, int);
void setSpeed(wheel, int);

void start_L(bool back=false);
void start_R(bool back=false);

void stop_L();
void stop_R();
void turn_L();
void turn_R();

#endif
