#include "mcc_generated_files/system/system.h"
#include "pwm.h"
#define PWM_PIN 13
#define CLK_PER 4000000UL
#define PRESCALER 4

void pwm_init(){
    PORTD.DIRSET = (1 << PWM_PIN);
    PORTMUX.TCAROUTEA = PORTMUX_TCA0_PORTD_gc;
    TCA0.SINGLE.CTRLB = TCA_SINGLE_CMP1EN_bm            /* enable compare channel 1 */
                      | TCA_SINGLE_WGMODE_DSBOTTOM_gc;  /* set dual-slope PWM mode */
    TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV4_gc       /* set clock source (sys_clk/4) */
                      | TCA_SINGLE_ENABLE_bm;           /* start timer */    
}

void pwm_play_tone(float frequency){
    float period = (float)CLK_PER / (4.0f * PRESCALER * frequency);
    /* set PWM frequency and duty cycle (50%) */
    TCA0.SINGLE.PERBUF  = period;
    TCA0.SINGLE.CMP1BUF = period / 2.0f;
}