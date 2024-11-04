// Draws an image that bounces around the screen

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// width and height of the image
#define LOGO_WIDTH 32
#define LOGO_HEIGHT 19

const unsigned char dvd_logo [] PROGMEM = {
	0xe0, 0x01, 0xf0, 0x07, 0xe0, 0x01, 0xe0, 0x01, 0xe7, 0x81, 0xc0, 0xf0, 0xc7, 0x80, 0xcc, 0x78, 
	0xc7, 0x88, 0x88, 0xf8, 0x8f, 0x18, 0x18, 0xf1, 0x80, 0x3c, 0x38, 0x03, 0x80, 0xfc, 0x78, 0x0f, 
	0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x3f, 0x00, 0x0f, 0x80, 0x03, 
	0x80, 0x0f, 0x80, 0x03, 0xf8, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xed, 0xb1, 0xce, 0x5f, 0xf3, 0xb6, 0xde, 0xdf, 0xf7, 0xb1, 0xcf, 0x3f
};

#define SCREEN_WIDTH 128      // OLED display width, in pixels
#define SCREEN_HEIGHT 64      // OLED display height, in pixels
#define OLED_RESET -1         // Reset pin, set to -1 to share Arduino reset pin
#define SCREEN_ADDRESS 0x3D   // 7-bit I2C Address, see CNANO-Explorer User Guide 6.3.7

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  delay(1000); // Wait for the display to ready
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    for(;;); // Display not connected or malfunctioning, loop forever
  }
  display.clearDisplay();
  display.display();
}

// bouncing logo
uint16_t bounceX = 0;
uint16_t bounceY = 0;
bool movingRight = true;  // if we're not moving right, we're moving left
bool movingDown = false;  // if we're not moving down, we're moving up

void loop() {
  if (bounceX == 0) {
    movingRight = true;
  } else if (bounceX == SCREEN_WIDTH - LOGO_WIDTH - 1) {
    movingRight = false;
  }
  if (movingRight) {
    bounceX++;
  } else {
    bounceX--;
  }

  if (bounceY == 0) {
    movingDown = true;
  } else if (bounceY == SCREEN_HEIGHT - LOGO_HEIGHT - 1) {
    movingDown = false;
  }
  if (movingDown) {
    bounceY++;
  } else {
    bounceY--;
  }

  display.clearDisplay();
  display.drawBitmap(bounceX, bounceY, dvd_logo, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}
