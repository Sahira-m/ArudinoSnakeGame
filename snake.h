#ifndef __SNAKE_H_
#define __SNAKE_H_
#include "joystick.h"

typedef struct{
    char x;
    char y; 
}Position;


typedef struct{
    char currentSnakeLength;
    Position snakePostion[X_AXIS_MAX * Y_AXIS_MAX]; 
}Snake; 


typedef enum {
    Snake_Up,
    Snake_down,
    Snake_left,
    Snake_right
}Movement; 

Movement snakeInit(Snake *snake, Movement snakeMoveDirection);
void automaticSnakeMovement(Snake *snake, Movement snakeMoveDirection);
void clearSnakeTail(Snake snake); 
void moveSnakeSegments(Snake *snake);
unsigned int legalSnakeMovement(Movement currentMove, int horizontal, int vertical);
unsigned int snakeHasMoved(int horizontal, int vertical, Movement *snakeMoveDirection);
unsigned int snakeCollision(Snake snake);
char randomPlacement(randomMax);
#endif