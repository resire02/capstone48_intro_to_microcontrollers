#include <tinyNeoPixel.h>
#include "Adafruit_MCP23008.h"

#define SPEAKER_PIN PIN_PA7
/**
  Requires remapping 
  -> PA7 to Speaker AMP-IN
**/

Adafruit_MCP23008 doorBell;

void initializeDoorBell() {
  PORTMUX.TCAROUTEA = PORTMUX_TCA0_PORTD_gc;
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

void doorBellLoop() {
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