#include <tinyNeoPixel.h>

tinyNeoPixel pixel_ring = tinyNeoPixel(8, PIN_PC3, NEO_GRB + NEO_KHZ800);
unsigned long color_grid[3] = {0x00007f,0x007f00,0x7f0000};

void setup() {
  pixel_ring.begin();
}

void loop() {
  static unsigned long ring_timer = 0UL;
  unsigned long now;
  static uint8_t pixel_index = 0,color_index = 0;

  now = millis();
  if(now - ring_timer > 211UL)
  {
    ring_timer = now;
    pixel_ring.clear();
    pixel_ring.show();
    pixel_ring.setPixelColor(pixel_index,color_grid[color_index]);
    pixel_ring.show();
    pixel_index++;
    if(pixel_index > 7)
            pixel_index = 0;
    color_index++;
    if(color_index >= 3)
      color_index = 0;
  }
}