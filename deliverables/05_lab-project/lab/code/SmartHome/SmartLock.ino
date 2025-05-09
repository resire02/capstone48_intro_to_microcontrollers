#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>

#define SCREEN_WIDTH 128      // OLED display width, in pixels
#define SCREEN_HEIGHT 64      // OLED display height, in pixels
#define OLED_RESET -1         // Reset pin, set to -1 to share Arduino reset pin
#define SCREEN_ADDRESS 0x3D   // 7-bit I2C Address
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
uint8_t pos = 5;

#define PASSWORD_SLOT 11

void initializePassword() {
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
  Serial.swap(3);
  Serial.begin(115200);
  delay(100);
  checkForStoredPassword();
  Serial.println("Login success!");
}

void checkForStoredPassword() {
  Serial.println("Welcome!");
  if (EEPROM.read(PASSWORD_SLOT) != 0xFF) {
    Serial.println("Password found. Please enter the stored password.");
    handlePasswordInput(false);
  }
  else {
    Serial.println("No password found. Create a new one.");
    handlePasswordInput(true);
  }
}

void handlePasswordInput(bool newUser) {
  Serial.println(newUser ? "Create a new password:" : "Enter your password:");
  String input;
  bool passed = false;
  while (!passed) {
    pos = 5;
    if (Serial.available() > 0) {
      input = Serial.readStringUntil('\n'); // Read the input until newline
      if (input.length() == 6) {
        for (int i = 0; i < 6; i++) {
          char displayChar = (i < input.length()) ? input[i] : ' ';
          display.drawChar(pos, 20, displayChar, 1, 0, 2);
          display.drawChar(pos, 40, '_', 1, 0, 2);
          pos += 20;
        }
        if (newUser) {
          passed = true;
          savePassword(input);          
        }
        else {
          if (verifyPassword(input)) {
            passed = true;
          }
          else {
            Serial.println("Incorrect Password. Try Again.");
          }
        }        
      }
      else {
        Serial.println("Password must be exactly 6 characters. Try again.");
      }
    }
    display.display();
  }
}

void savePassword(String input) {
  for (int i = 0; i < 6; i++) {
    int cell = i + 11;
    int digit = input[i] - '0';
    EEPROM.update(cell, digit);
  }
  int read_value;
  for (EEPtr ptr = 11; ptr.index < 17; ptr++) {
    read_value = *ptr;
  }
}

bool verifyPassword(String input) {
  int read_value;
  int i = 0;
  for (EEPtr ptr = 11; ptr.index < 17; ptr++) {
    read_value = *ptr;
    int digit = input[i] - '0';
    if (digit != read_value) {
      return false;
    }
    i++;
  }
  return true;
}
