#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128      // OLED display width, in pixels
#define SCREEN_HEIGHT 64      // OLED display height, in pixels
#define OLED_RESET -1         // Reset pin, set to -1 to share Arduino reset pin
#define SCREEN_ADDRESS 0x3D   // 7-bit I2C Address
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
uint8_t pos = 5;

void setup() {
  Serial.swap(3);
  Serial.begin(115200);
  delay(1000); // Wait for the display to ready
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    for(;;); // Display not connected or malfunctioning, loop forever
  }
  display.clearDisplay();
  for (int i = 0; i < 6; i++) {
    display.drawChar(pos, 40, '_', 1, 0, 2);
    display.drawChar(pos, 40, ' ', 1, 0, 1);
    pos += 20;
  }
  display.display(); // Display draw operations on screen
  delay(100);
  Serial.println("Welcome! Please enter your password. It will pop up on your board's OLED screen.");
}

void loop() {
  String input;
  if (Serial.available() > 0) {
    input = Serial.readStringUntil('\n'); // Read the input until newline
    Serial.println(input);
  }
  pos = 5;
  if (input.length()) {
    for (int i = 0; i < 6; i++) {
      char displayChar = (i < input.length()) ? input[i] : ' ';
      display.drawChar(pos, 20, displayChar, 1, 0, 2);
      display.drawChar(pos, 40, '_', 1, 0, 2);
      pos += 20;
    }
  }
  display.display();
}
