#include "max72xx.h"
#include <stdint.h>
#include "analogRead.h"
#include "joystick.h"
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include <time.h>
#include <stdlib.h>
#include "uart.h"
#include "snake.h"
#include "food.h"
#include "millis.h"
#include <avr/interrupt.h>

#define VERT_PIN 0
#define HORZ_PIN 1
#define SEL_PIN 2

#define BIT_SET(a, b) ((a) |= (1ULL << (b)))
#define BIT_CLEAR(a, b) ((a) &= ~(1ULL << (b)))
#define BIT_CHECK(a, b) (!!((a) & (1ULL << (b))))

#define BUTTON_IS_CLICKED(PINB, BUTTON_PIN) !BIT_CHECK(PINB, BUTTON_PIN)

void hardwareInit()
{
    BIT_CLEAR(DDRC, VERT_PIN);
    BIT_CLEAR(DDRC, HORZ_PIN);

    // Sätt till INPUT_PULLUP
    BIT_CLEAR(DDRD, SEL_PIN); // INPUT MODE
    BIT_SET(PORTD, SEL_PIN);

    millis_init();
    sei();
    init_serial();
    max7219_init();
    return;
}

//// https://wokwi.com/projects/296234816685212169

int main()
{
    hardwareInit();

    uint8_t letterSpace = 0;

    // clearLedMatrix(X_AXIS_MAX, Y_AXIS_MAX);
    Snake snake;
    Movement snakeMoveDirection = snakeInit(&snake, snakeMoveDirection);
    Food food;
    foodInit(&food);
    generateFood(&food, snake);
    int horizontal;
    int vertical;
    volatile millis_t millisecondsSinceLastAction = 0;
    letterSpace = 0;

    while (1)
    {
        // Moves snake one LED in the current snakeMoveDirection if no move has been made for 175 milliseconds.
        if (millis_get() - millisecondsSinceLastAction > 175)
        {
            moveSnakeSegments(&snake);
            automaticSnakeMovement(&snake, snakeMoveDirection);
            if (snakeCollision(snake))
            {

                break;
            };
            millisecondsSinceLastAction = millis_get();
        }

        // Reads and stores joystick-input
        horizontal = analogRead(HORZ_PIN);
        vertical = analogRead(VERT_PIN);

        if (legalSnakeMovement(snakeMoveDirection, horizontal, vertical))
        {
            if (snakeHasMoved(horizontal, vertical, &snakeMoveDirection))
            {
                millisecondsSinceLastAction = millis_get();
                moveSnakeSegments(&snake);
            }
            snake.snakePostion[0].x = joystickXAxis(horizontal, snake.snakePostion[0].x);
            snake.snakePostion[0].y = joystickYAxis(vertical, snake.snakePostion[0].y);
            max7219b_set(snake.snakePostion[0].x, snake.snakePostion[0].y);
            if (snakeCollision(snake))
            {

                break;
            }
        }
        max7219b_out();
        clearSnakeTail(snake);

        // Checks if the "head" (segment [0]) is on the same position as the food.
        // If it is, the snake grows and a new food is generated. If its not possible to generate food. Player wins the game
        if (snake.snakePostion[0].x == food.foodX && snake.snakePostion[0].y == food.foodY)
        {
            snake.currentSnakeLength++;
            if (!generateFood(&food, snake))
            {
                // clearLedMatrix(X_AXIS_MAX, Y_AXIS_MAX);
                // letterSpace = (Win.letterW, letterSpace + 1);
                // letterSpace = printLetterToLED(Win.letterI, letterSpace);
                // letterSpace = printLetterToLED(Win.letterN, letterSpace);
                break;
            }
        }
    }
    return 0;
}