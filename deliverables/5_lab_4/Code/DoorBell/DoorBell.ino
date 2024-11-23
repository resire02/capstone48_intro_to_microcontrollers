#include <Dx_PWM.h>
#include "notes.h"

/**
  Requires remapping 
  -> PWM4 to Speaker AMP-IN 
  -> 27 (IO 2) to SW 2 (middle touch sensor)
**/
#define DOOR_BELL PIN_PC3
#define SPEAKER_PIN PIN_PD2

#define NOTE_PERIOD 750

#define DOOR_NOTES_COUNT 2
float door_notes[] = {NOTE_A6S, NOTE_F6S};

Dx_PWM* speaker;

void setup() {
  pinMode(DOOR_BELL, INPUT_PULLUP);
  
  PORTMUX.TCAROUTEA = PORTMUX_TCA0_PORTD_gc;
  speaker = new Dx_PWM(SPEAKER_PIN, 1000.0f, 0.0f);

  Serial.swap(3);
  Serial.begin(9600);
  while (!Serial);
}

int bell_value;

void loop() {
  static int speaker_index = -1;
  static uint16_t speaker_timer = 0;
  uint16_t now = millis();

  if (speaker_index != -1 && now - speaker_timer > NOTE_PERIOD) {
    speaker_timer = now;
    speaker_index++;
    if (speaker_index < DOOR_NOTES_COUNT) {
      speaker->setPWM(SPEAKER_PIN, door_notes[speaker_index], 0.0f);
    } else {
      speaker_index = -1;
      speaker->setPWM(SPEAKER_PIN, 0.0f, 0.0f);
    }
  }

  bell_value = digitalRead(DOOR_BELL);
  if (bell_value == LOW && speaker_index == -1) {
    speaker_index = 0;
    speaker->setPWM(SPEAKER_PIN, door_notes[speaker_index], 0.0f);
    speaker_timer = now;
  }

  Serial.printf("Sensor: %d\tIndex: %d\n", bell_value, speaker_index);
}
