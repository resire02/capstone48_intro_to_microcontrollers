#include "mcc_generated_files/system/system.h"
#include <xc.h>

static volatile uint32_t timer1 = 0UL,
                         timer2 = 0UL;

void timer_callback(void)
{
    cli();
    timer1++;
    timer2++;
    sei();
}

void timer_init()
{
    Timer0.TimeoutCallbackRegister(timer_callback);
}

void clear_timer1()
{
    cli();
    timer1 = 0;
    sei();
}

uint32_t read_timer1()
{
    uint32_t val;
    cli();
    val = timer1;
    sei();
    return val;
}

void clear_timer2()
{
    cli();
    timer2 = 0;
    sei();
}

uint32_t read_timer2()
{
    uint32_t val;
    cli();
    val = timer2;
    sei();
    return val;
}
