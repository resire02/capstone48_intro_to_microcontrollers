#include "Dx_PWM.h"
#include "pwm_notes.h"

Dx_PWM *pwmModulator;

#define NOTE_COUNT 4

void setup() {
  PORTMUX.TCAROUTEA = PORTMUX_TCA0_PORTD_gc;
  pwmModulator = new Dx_PWM(PIN_PD1, 0.0f, 50.0f);
}

void loop() {
  pwmModulator->setPWM(PIN_PD1, 220.0f, 25.0f);
  delay(1000);
  pwmModulator->setPWM(PIN_PD1, 440.0f, 25.0f);
  delay(1000);
  pwmModulator->setPWM(PIN_PD1, 880.0f, 25.0f);
  delay(1000);
}