// Lab 2 example draw operations

// external libraries needed to work with the ssd1306 OLED display
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128      // OLED display width, in pixels
#define SCREEN_HEIGHT 64      // OLED display height, in pixels
#define OLED_RESET -1         // Reset pin, set to -1 to share Arduino reset pin
#define SCREEN_ADDRESS 0x3D   // 7-bit I2C Address, see CNANO-Explorer User Guide 6.3.7

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  delay(1000); // Wait for display to ready

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    for(;;);
  }

  display.clearDisplay(); // clear the Adafruit logo

  display.fillRect(0, 0, 40, 20, 1);  // Draws a 40px by 20px rectangle at (0,0)
  display.drawPixel(80, 40, 1);       // Draws a pixel at (80, 40)
  display.drawCircle(80, 40, 20, 1);  // Draws a circle with 20px radius at (80, 40)
  display.drawChar(20, 40, 'A', 1, 0, 2); // Draws 'A' of size 2 at (20,40)

  display.display(); // Display draw operations on screen
}

void loop() {
  // do nothing
}