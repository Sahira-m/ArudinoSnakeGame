#ifndef __JOYSTICK_H_
#define __JOYSTICK_H_

#include <avr/io.h>
#include "max72xx.h"
#define X_AXIS_MAX 16
#define Y_AXIS_MAX 8

int joystickXAxis(int horz, int x); 
int joystickYAxis(int vert, int y); 

#endif