#ifndef _FOOD_H_
#define _FOOD_H_
#include <stdint.h>
#include "snake.h"

typedef struct{
    char foodX;
    char foodY; 
}Food; 

void foodInit(Food *food); 
uint8_t generateFood(Food *food, Snake snake); 
#endif