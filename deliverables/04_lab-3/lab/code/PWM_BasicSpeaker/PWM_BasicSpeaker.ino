#include "Dx_PWM.h"

// define the PWM pin as PWM-A
#define PWM_PIN PIN_PD1

Dx_PWM *pwmModulator;

void setup() {
  // reroute the TCA timer and sets up the PWM class
  PORTMUX.TCAROUTEA = PORTMUX_TCA0_PORTD_gc;
  pwmModulator = new Dx_PWM(PIN_PD1, 0.0f, 50.0f);
}

void loop() {
  // plays the C major scale infinitely
  pwmModulator->setPWM(PWM_PIN, 523.251f, 50.0f);
  delay(1000);
  pwmModulator->setPWM(PWM_PIN, 587.33f, 50.0f);
  delay(1000);
  pwmModulator->setPWM(PWM_PIN, 659.255f, 50.0f);
  delay(1000);
  pwmModulator->setPWM(PWM_PIN, 698.456f, 50.0f);
  delay(1000);
  pwmModulator->setPWM(PWM_PIN, 783.991f, 50.0f);
  delay(1000);
  pwmModulator->setPWM(PWM_PIN, 880.0f, 50.0f);
  delay(1000);
  pwmModulator->setPWM(PWM_PIN, 987.767f, 50.0f);
  delay(1000);
  pwmModulator->setPWM(PWM_PIN, 1046.502f, 50.0f);
  delay(1000);
}
