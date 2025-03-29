#ifndef SIMPLETIMER_H
#define	SIMPLETIMER_H

#ifdef	__cplusplus
extern "C" {
#endif
    
void timer_callback();
void clear_timer();
uint32_t read_timer();

#ifdef	__cplusplus
}
#endif

#endif	/* SIMPLETIMER_H */

