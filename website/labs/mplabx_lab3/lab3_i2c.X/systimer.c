#include "mcc_generated_files/system/system.h"
#include <xc.h>

static volatile uint32_t timer = 0UL;

void timer_callback()
{
    cli();
    timer++;
    sei();
}

void clear_timer()
{
    cli();
    timer = 0;
    sei();
}

uint32_t read_timer()
{
    uint32_t val;
    cli();
    val = timer;
    sei();
    return val;
}