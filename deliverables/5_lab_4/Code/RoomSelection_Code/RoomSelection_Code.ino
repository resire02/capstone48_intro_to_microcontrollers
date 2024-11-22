#define POTMETERPIN 19
#include <tinyNeoPixel.h>

tinyNeoPixel pixel_ring = tinyNeoPixel(8, PIN_PC3, NEO_GRB + NEO_KHZ800);
unsigned long color_grid[3] = {0x00007f,0x007f00,0x7f0000}; // Red, green, and blue

void setup() {
  // put your setup code here, to run once:
  pixel_ring.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t pixel_index = 0, color_index = 0;

  int readValue = analogRead(POTMETERPIN);

  while(readValue > 128) {
    readValue = readValue - 128; 
    pixel_index++;
  }

  pixel_ring.clear();
  pixel_ring.show();
  pixel_ring.setPixelColor(pixel_index, color_grid[color_index]);
  pixel_ring.show();
}
