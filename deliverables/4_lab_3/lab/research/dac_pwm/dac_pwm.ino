#include "Dx_PWM.h"
#include "pwm_notes.h"

Dx_PWM *pwmModulator;

#define RESONANCE_SHAPE 5.0f
#define BEEP_SHAPE 25.0f
#define SQUARE_SHAPE 50.0f

void setup() {
  PORTMUX.TCAROUTEA = PORTMUX_TCA0_PORTD_gc;
  pwmModulator = new Dx_PWM(PIN_PD1, 0.0f, 50.0f);
}

// First distinct note at NOTE_F5
void loop() {
  // Cm7 chord
  pwmModulator->setPWM(PIN_PD1, NOTE_C6, RESONANCE_SHAPE);
  delay(500);
  pwmModulator->setPWM(PIN_PD1, NOTE_D6S, BEEP_SHAPE);
  delay(500);
  pwmModulator->setPWM(PIN_PD1, NOTE_G6, SQUARE_SHAPE);
  delay(500);
  pwmModulator->setPWM(PIN_PD1, NOTE_A6S, SQUARE_SHAPE);
  delay(500);
}