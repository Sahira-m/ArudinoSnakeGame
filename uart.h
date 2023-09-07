

#ifndef UART_H
#define UART_H
#include <stdio.h>

int uart_putchar(char c, FILE *stream);
int uart_getchar(FILE *stream);

void uart_init(void);

void init_serial();

#endif