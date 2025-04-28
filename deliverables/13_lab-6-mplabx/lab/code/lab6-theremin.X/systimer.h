/*
 * Interrupt based timer
 */

#ifndef SYSTIMER_H
#define	SYSTIMER_H

#ifdef	__cplusplus
extern "C" {
#endif
    
void timer_init(void);
void clear_timer();
uint32_t read_timer();

#ifdef	__cplusplus
}
#endif

#endif	/* SYSTIMER_H */

