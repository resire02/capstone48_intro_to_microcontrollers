#ifndef PWM_H
#define	PWM_H

#ifdef	__cplusplus
extern "C" {
#endif

void pwm_init();
void pwm_play_tone(float frequency, float duty_cycle);

#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

