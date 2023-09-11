#include "max72xx.h"
#include "analogRead.h"
#include "joystick.h"
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include <time.h>
#include <stdlib.h>
#include "uart.h"
#include "randomPlacement.h"

#define VERT_PIN 0
#define HORZ_PIN 1
#define SEL_PIN 2

#define BIT_SET(a, b) ((a) |= (1ULL << (b)))
#define BIT_CLEAR(a, b) ((a) &= ~(1ULL << (b)))
#define BIT_FLIP(a, b) ((a) ^= (1ULL << (b)))
#define BIT_CHECK(a, b) (!!((a) & (1ULL << (b))))

#define BUTTON_IS_CLICKED(PINB, BUTTON_PIN) !BIT_CHECK(PINB, BUTTON_PIN)

// wokwi url to attach .hex file  https://wokwi.com/projects/296234816685212169

int main()
{
    BIT_CLEAR(DDRC, VERT_PIN);
    BIT_CLEAR(DDRC, HORZ_PIN);

    BIT_CLEAR(DDRD, SEL_PIN);
    BIT_SET(PORTD, SEL_PIN);

    init_serial();
    max7219_init();
    srand(analogRead(SEL_PIN));
    int snakeX = randomPlacement(X_AXIS_MAX);
    // print("\n X_AXIS_MAX:", snakeX);
    int snakeY = randomPlacement(Y_AXIS_MAX);
    // print("\n Y_AXIS_MAX:", Y_AXIS_MAX);
    int foodX = randomPlacement(X_AXIS_MAX);
    // print("\n X_AXIS_MAX:", X_AXIS_MAX);
    int foodY = randomPlacement(Y_AXIS_MAX);
    // print("\n Y_AXIS_MAX:", Y_AXIS_MAX);
    while (snakeX == foodX && snakeY == foodY)
    {
        foodX = randomPlacement(X_AXIS_MAX);
        foodY = randomPlacement(Y_AXIS_MAX);
    }
    int lastX = 0;
    int lastY = 0;

    printf("x = %d\n", snakeX);
    printf("y = %d\n", snakeY);
    printf("Food x = %d\n", foodX);
    printf("Food y = %d\n", foodY);
    max7219b_set(snakeX, snakeY);
    max7219b_set(foodX, foodY);
    max7219b_out();

    while (1)
    {
        int horz = analogRead(HORZ_PIN);
        int vert = analogRead(VERT_PIN);
        max7219b_clr(lastX, lastY);
        snakeX = joystickXAxis(horz, snakeX);
        snakeY = joystickYAxis(vert, snakeY);

        max7219b_set(snakeX, snakeY);
        max7219b_out();
        _delay_ms(100);
        lastX = snakeX;
        lastY = snakeY;

        while (snakeX == foodX && snakeY == foodY)
        {
            foodX = randomPlacement(X_AXIS_MAX);
            foodY = randomPlacement(Y_AXIS_MAX);
            max7219b_set(foodX, foodY);
            max7219b_out();
        }
    }
    return 0;
}