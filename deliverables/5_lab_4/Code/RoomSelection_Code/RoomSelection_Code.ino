#define POTMETERPIN 19
#define SWITCH_ONE 22
#define SWITCH_TWO 8
#define SWITCH_THREE 9
#include <tinyNeoPixel.h>

tinyNeoPixel pixel_ring = tinyNeoPixel(8, PIN_PC3, NEO_GRB + NEO_KHZ800);
unsigned long color_grid[3] = {0x00007f,0x007f00,0x7f0000}; // Red, green, and blue

void setup() {
  // put your setup code here, to run once:
  pixel_ring.begin();
  pinMode(SWITCH_ONE, INPUT);
  pinMode(SWITCH_TWO, INPUT);
  pinMode(SWITCH_THREE, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t pixel_index = 0;
  static uint8_t color_index[8] = {0};

  int readValue = analogRead(POTMETERPIN);

  while(readValue > 128) {
    readValue = readValue - 128; 
    pixel_index++;
  }

  int switch_one_value = digitalRead(SWITCH_ONE);
  int switch_two_value = digitalRead(SWITCH_TWO);
  int switch_three_value = digitalRead(SWITCH_THREE);

  color_index[pixel_index] = switch_one_value == LOW ? 0 : switch_two_value == LOW ? 1 : switch_three_value == LOW ? 2 : color_index[pixel_index];

  pixel_ring.clear();
  pixel_ring.show();
  pixel_ring.setPixelColor(pixel_index, color_grid[color_index[pixel_index]]);
  pixel_ring.show();
}
