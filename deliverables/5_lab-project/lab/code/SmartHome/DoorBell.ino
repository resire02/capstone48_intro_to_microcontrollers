#include <Dx_PWM.h>
#include "notes.h"
#include <tinyNeoPixel.h>
#include "Adafruit_MCP23008.h"
/**
  Requires remapping 
  -> PWM4 to Speaker AMP-IN 
  -> 26 (IO 2) to TS4 Sensor (logo touch sensor)
  -> 27 (IO 2) to SW 2 (middle touch sensor) (if capacitive touch button not working)
**/

Adafruit_MCP23008 doorBell;
float door_notes[] = {NOTE_A6S, NOTE_F6S};

#define SPEAKER_PIN PIN_PD2
#define NOTE_PERIOD 750
#define DOOR_NOTES_COUNT 2

Dx_PWM* speaker;

void initializeDoorBell() {
  uint8_t pin_id;
  doorBell.begin(0x24);
  for (pin_id = 0; pin_id < 5; pin_id++) {
    doorBell.pinMode(pin_id, INPUT);
    doorBell.pullUp(pin_id, HIGH);
  }
  
  pinMode(SPEAKER_PIN, OUTPUT);

  PORTMUX.TCAROUTEA = PORTMUX_TCA0_PORTD_gc;
  speaker = new Dx_PWM(SPEAKER_PIN, 1000.0f, 0.0f);

  Serial.swap(3);
  Serial.begin(115200);
  while (!Serial);
}

bool prev_jIn = false;
int prev_bell_value = -1;
int prev_speaker_index = -1;

void doorBellLoop() {
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

  bool jIn = !doorBell.digitalRead(4);
  if (jIn == HIGH && speaker_index == -1) {
    speaker_index = 0;
    speaker->setPWM(SPEAKER_PIN, door_notes[speaker_index], 0.0f);
    speaker_timer = now;
  }

  if (jIn != prev_jIn) {
    Serial.println(jIn ? "Ringing bell!" : "Bell released!");
    prev_jIn = jIn; // Update the previous state
  }
    
}