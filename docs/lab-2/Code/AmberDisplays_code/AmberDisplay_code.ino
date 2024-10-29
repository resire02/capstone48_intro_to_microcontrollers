/*

  MakerFaire 2024 Demo 
  AVR64DD32 + CNano Board

  This is the extracted version of the cycling LEDS from the MakerFaire 2024 Demo, all credit to the original
  creator of the demo
*/


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Adafruit_MCP23008.h"
// #include <Adafruit_NeoPixel.h>
#include <tinyNeoPixel.h>

Adafruit_MCP23008 mcp_leds;

void setup() {
  uint8_t pin_id, status;

  status = mcp_leds.begin(0x25);

  for (pin_id = 0; pin_id < 8; pin_id++) {
    mcp_leds.pinMode(pin_id, OUTPUT);
    mcp_leds.digitalWrite(pin_id, HIGH);
  }
}

void loop() {
  cylon();
}

void cylon(void) {
  static uint8_t led_index = 0, led_state = false, led_dir = true;
  static unsigned long cylon_timer = 0UL;
  unsigned long now;

  now = millis();
  if (now - cylon_timer > 37UL) {
    cylon_timer = now;
    if (led_state) {
      led_state = false;
      mcp_leds.digitalWrite(led_index, HIGH);
    } else {
      led_state = true;
      mcp_leds.digitalWrite(led_index, LOW);
    }

    if (led_state == false) {
      if (led_dir) {
        led_index++;
        if (led_index > 7) {
          led_index = 7;
          led_dir = false;
        }
      } else {
        led_index--;
        if (led_index > 127)  // unsigned 8 bit gone negative
        {
          led_index = 0;
          led_dir = true;
        }
      }
    }
  }
}