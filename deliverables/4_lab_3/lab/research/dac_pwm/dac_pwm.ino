/**
  Code for PWM and the speaker working together.
  Plays a snippet of Fur Elise - Mozart
  Need to reroute PWM-A (PIN D1) to speaker AMP-IN (MCP4821)
**/
#include "Dx_PWM.h"
#include "pwm_notes.h"

Dx_PWM *pwmModulator;

#define PWM_PIN PIN_PD1

#define QUARTER_NOTE 850
#define EIGHTH_NOTE 425

#define RESONANCE_SHAPE 5.0f
#define BEEP_SHAPE 25.0f
#define SQUARE_SHAPE 50.0f

float melody_notes[] = {
  NOTE_E7, NOTE_D7S, NOTE_E7, NOTE_D7S, NOTE_E7,
  NOTE_B6, NOTE_D7, NOTE_C7, NOTE_A6,
  NOTE_C6, NOTE_E6, NOTE_A6, NOTE_B6,
  NOTE_E6, NOTE_G6S, NOTE_B6, NOTE_C7,
  NOTE_E6, NOTE_E7, NOTE_D7S, NOTE_E7, NOTE_D7S, NOTE_E7,
  NOTE_B6, NOTE_D7, NOTE_C7, NOTE_A6,
  NOTE_C6, NOTE_E6, NOTE_A6, NOTE_B6,
  NOTE_E6, NOTE_C7, NOTE_B6, NOTE_A6,
  NOTE_B6, NOTE_C7, NOTE_D7, NOTE_E7,
  NOTE_G6, NOTE_F7, NOTE_E7, NOTE_D7,
  NOTE_F6, NOTE_E7, NOTE_D7, NOTE_C7,
  NOTE_E6, NOTE_D7, NOTE_C7, NOTE_B6,
};

uint32_t melody_duration[] = {
  EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE,
  EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE, QUARTER_NOTE,
  EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE, QUARTER_NOTE,
  EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE, QUARTER_NOTE,
  EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE,
  EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE, QUARTER_NOTE,
  EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE, QUARTER_NOTE,
  EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE, QUARTER_NOTE,
  EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE, QUARTER_NOTE,
  EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE, QUARTER_NOTE,
  EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE, QUARTER_NOTE,
  EIGHTH_NOTE, EIGHTH_NOTE, EIGHTH_NOTE, QUARTER_NOTE,
};

int16_t melody_length = (int16_t) (sizeof(melody_notes) / sizeof(float));

void setup() {
  PORTMUX.TCAROUTEA = PORTMUX_TCA0_PORTD_gc;
  pwmModulator = new Dx_PWM(PIN_PD1, 0.0f, 50.0f);
}

int melody_index;

// Usage: pwmModulator->setPWM(PWM_PIN, FREQ, DUTY_CYCLE);
// First distinct note at NOTE_F5
void loop() {
  for (melody_index = 0; melody_index < melody_length; melody_index++) {
    pwmModulator->setPWM(PWM_PIN, melody_notes[melody_index], BEEP_SHAPE);
    delay(melody_duration[melody_index]);
  }
}