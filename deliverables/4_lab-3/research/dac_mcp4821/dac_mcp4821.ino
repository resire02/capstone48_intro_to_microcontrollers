#include <SPI.h>
#include <MCP_DAC.h>

#define SPI_MOSI 4  // PA4
#define SPI_SCK 6   // PA6
#define DAC_CS 10   // PC2

MCP4821 dac(SPI_MOSI, SPI_SCK); // initialize DAC library

#define NUM_NOTES 9
uint16_t notes[9] = {3, 4, 5, 6, 7, 8, 9, 10, 11};

uint16_t pattern[9] = {1000, 250, 250, 250, 250, 500, 500, 1000, 1000};

void setup() {
  dac.begin(DAC_CS);
}

void loop() {
  static uint8_t index = 0;
  static uint16_t timer = 0;
  static bool ascending = true;
  uint16_t now = millis();
  
  dac.write(1000);  // this only controls volume
  dac.write(0);     // creates a pseudo square wave
  delay(notes[index]);  // determines note frequency

  if (now - timer > pattern[index]) {
    timer = now;

    // ascend and descend notes
    if (ascending) {
      index++;
    } else {
      index--;
    }

    // change direction if at boundary
    if (index == 0) {
      ascending = true;
    } else if (index == NUM_NOTES - 1) {
      ascending = false;
    }
  }
}
