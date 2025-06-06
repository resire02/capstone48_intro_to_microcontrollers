
/*
 
 
     soft timer module 
 configure and set up three 1 ms timers driven by an ISR on TCB0
 
 
 
 
 
 
 */


#include "mcc_generated_files/system/system.h"
#include <string.h>
#include <stdio.h>
#include <util/delay.h>
#include "systimer.h"

volatile uint32_t timer1, timer2, timer3 = 0UL;



// connect soft timer ISR to callback for TCB0 in tcb0.c

void systimer_init(void)
{
   Timer0.TimeoutCallbackRegister(tcb_softtimer);
   clear_timer1();
   clear_timer2();
   clear_timer3();
}


void tcb_softtimer(void)
{

    // PORTC.OUTSET = (1 << 3);
    cli();
    timer1++;
    timer2++;
    timer3++;
    sei();
    // PORTC.OUTCLR = (1 << 3);
}

void clear_timer1(void)
{
    cli();
    timer1 = 0;
    sei();
}

void clear_timer2(void) 
{
    cli();
    timer2 = 0;
    sei();
}

uint32_t read_timer1(void)
{
    uint32_t timer1_val;

    cli();
    timer1_val = timer1;
    sei();
    return (timer1_val);
}

uint32_t read_timer2(void) 
{
    uint32_t timer2_val;

    cli();
    timer2_val = timer2;
    sei();

    return (timer2_val);
}


void clear_timer3(void) 
{
    cli();
    timer3 = 0;
    sei();
}

uint32_t read_timer3(void) 
{
    uint32_t timer3_val;

    cli();
    timer3_val = timer3;
    sei();
    return (timer3_val);

}