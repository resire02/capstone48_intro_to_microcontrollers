#include <Dx_PWM.h>
#include "notes.h"
#include <tinyNeoPixel.h>
#include "Adafruit_MCP23008.h"
/**
  Requires remapping 
  -> PA1 to Speaker AMP-IN
**/

Adafruit_MCP23008 doorBell;
float door_notes[] = {NOTE_A6S, NOTE_F6S};

#define SPEAKER_PIN PIN_PA1
#define NOTE_PERIOD 750
#define DOOR_NOTES_COUNT 2

void initializeDoorBell() {
  uint8_t pin_id;
  doorBell.begin(0x24);
  for (pin_id = 0; pin_id < 5; pin_id++) {
    doorBell.pinMode(pin_id, INPUT);
    doorBell.pullUp(pin_id, HIGH);
  }

  pinMode(SPEAKER_PIN, OUTPUT);
  Serial.swap(3);
  Serial.begin(115200);
  while (!Serial);
}

bool prev_jIn = false;
int prev_bell_value = -1;
int prev_speaker_index = -1;

void doorBellLoop() {

  uint16_t now = millis();

  bool jIn = !doorBell.digitalRead(4);
  if (jIn && !prev_jIn) { // Joystick pressed (rising edge)
      Serial.println("Ringing bell!");
      analogWrite(SPEAKER_PIN, 128); // Write a PWM value (adjust for your desired tone)
  } else if (!jIn && prev_jIn) { // Joystick released (falling edge)
      Serial.println("Bell released!");
      analogWrite(SPEAKER_PIN, 0); // Stop the sound
  }

  prev_jIn = jIn; // Update the previous state
    
}