/* 
 * File:   pwm.h
 * Author: Gonzalo Allendes
 *
 * Created on 20 de abril de 2025, 16:48
 */

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

