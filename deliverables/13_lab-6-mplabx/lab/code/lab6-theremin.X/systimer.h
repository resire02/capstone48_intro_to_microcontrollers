/*
 * Interrupt based timer
 */

#ifndef SYSTIMER_H
#define	SYSTIMER_H

#ifdef	__cplusplus
extern "C" {
#endif
    
void timer_init(void);
void clear_timer1();
uint32_t read_timer1();
void clear_timer2();
uint32_t read_timer2();

#ifdef	__cplusplus
}
#endif

#endif	/* SYSTIMER_H */

