#include "analogRead.h"

static inline void initADC0(void)
{
    ADMUX |= _BV(REFS0);
    ADCSRA |= _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
    ADCSRA |= _BV(ADEN);
}

uint16_t analogRead(uint8_t apin)
{

    initADC0();
    ADMUX |= (apin);

    ADMUX &= (0xF0);
    switch (apin)
    {
    case 0:
        break;
    case 1:
        ADMUX |= (_BV(MUX0));
        break;
    case 2:
        ADMUX |= (_BV(MUX1));
        ;
        break;
    case 3:
        ADMUX |= (_BV(MUX1) | _BV(MUX0));
        ;
        break;
    case 4:
        ADMUX |= (_BV(MUX2));
        ;
        break;
    case 5:
        ADMUX |= (_BV(MUX2) | _BV(MUX0));
        ;
        break;
    }

    ADCSRA |= _BV(ADSC);
    loop_until_bit_is_clear(ADCSRA, ADSC);
    return (ADC);
}