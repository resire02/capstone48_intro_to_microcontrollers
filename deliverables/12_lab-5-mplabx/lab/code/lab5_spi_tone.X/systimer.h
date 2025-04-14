/* 
 * File:   systimer.h
 * Author: C40769
 *
 * Created on February 26, 2025, 11:25 AM
 */

#ifndef SYSTIMER_H
#define	SYSTIMER_H

#ifdef	__cplusplus
extern "C" {
#endif

void systimer_init(void);
void tcb_softtimer(void);
void clear_timer1(void);
void clear_timer2(void);
void clear_timer3(void);
uint32_t read_timer1(void);
uint32_t read_timer2(void);
uint32_t read_timer3(void);


#ifdef	__cplusplus
}
#endif

#endif	/* SYSTIMER_H */

