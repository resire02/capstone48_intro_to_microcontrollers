#define POTMETERPIN 19
#define SWITCH_ONE 22
#define SWITCH_TWO 8
#define SWITCH_THREE 9

#include "Adafruit_MCP23008.h"
#include <tinyNeoPixel.h>

Adafruit_MCP23008 joystick;
tinyNeoPixel pixel_ring = tinyNeoPixel(8, PIN_PC3, NEO_GRB + NEO_KHZ800);
unsigned long color_grid[3] = { 0x00007f, 0x007f00, 0x7f0000 };  // Red, green, and blue

void initializeRoom() {
  Serial.swap(3);
  Serial.begin(115200);

  // put your setup code here, to run once:
  pixel_ring.begin();
  pixel_ring.clear();
  pixel_ring.show();
  pinMode(SWITCH_ONE, INPUT);
  pinMode(SWITCH_TWO, INPUT);
  pinMode(SWITCH_THREE, INPUT);

  uint8_t pin_id;
  joystick.begin(0x24);
  for (pin_id = 0; pin_id < 5; pin_id++) {
    joystick.pinMode(pin_id, INPUT);
    joystick.pullUp(pin_id, HIGH);
  }
}

bool prev_jUp = false;
bool prev_jLeft = false;
bool prev_jRight = false;
int previousPixelIndex = -1; // Variable to store the previous pixel index


void roomLoop() {
      // put your main code here, to run repeatedly:
  static uint8_t color_index[8] = { 0 };
  int readValue = analogRead(POTMETERPIN);
  uint8_t pixel_index = map(readValue, 0, 1023, 0, 7);  // Map to pixel index (0-7)

  // Check if the pixel index has changed
  if (pixel_index != previousPixelIndex) {
    previousPixelIndex = pixel_index;  // Update the previous pixel index
    Serial.print("Moving to room ");
    Serial.println(pixel_index);  // Print the new room (pixel index)
  }

  bool jUp = !joystick.digitalRead(0); 
  bool jLeft = !joystick.digitalRead(1);
  bool jRight = !joystick.digitalRead(3);

  // Check if the state of each button has changed
  if (jUp != prev_jUp) {
      Serial.println(jUp ? "Pushing Up!" : "Released Up!");
      prev_jUp = jUp; // Update the previous state
  }
  if (jLeft != prev_jLeft) {
      Serial.println(jLeft ? "Pushing Left!" : "Released Left!");
      prev_jLeft = jLeft; // Update the previous state
  }
  if (jRight != prev_jRight) {
      Serial.println(jRight ? "Pushing Right!" : "Released Right!");
      prev_jRight = jRight; // Update the previous state
  }

  int switch_one_value = digitalRead(SWITCH_ONE);
  int switch_two_value = digitalRead(SWITCH_TWO);
  int switch_three_value = digitalRead(SWITCH_THREE);

  color_index[pixel_index] = switch_one_value == LOW ? 0 : switch_two_value == LOW   ? 1
                                                         : switch_three_value == LOW ? 2
                                                         : color_index[pixel_index];

  pixel_ring.clear();
  pixel_ring.setPixelColor(pixel_index, color_grid[color_index[pixel_index]]);
  pixel_ring.show();
}
