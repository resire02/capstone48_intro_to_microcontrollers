// import the SPI and MCP_DAC libraries
#include <SPI.h>
#include <MCP_DAC.h>

// define the SPI pins for readability
#define SPI_COPI PIN_PA4
#define SPI_SCK PIN_PA6
#define DAC_CS PIN_PC2

// initialize DAC library with the Controller-In-Peripheral-Out 
// and Serial-Clock-Line pins
MCP4821 dac(SPI_COPI, SPI_SCK);

// largest value represented by 12-bits
#define MAX_VOLUME 4095

void setup() {
  // set up the DAC for writing
  dac.begin(DAC_CS);
}

void loop() {
  static uint16_t current_vol = 0;

  dac.write(current_vol); // this will not create any sound by itself
  dac.write(0); // creates a psuedo square wave
  delay(1);     // change this value to change the frequency

  current_vol++;
  if (current_vol >= MAX_VOLUME) {
    while (true) delay(1000); // sleep forever
  }
}