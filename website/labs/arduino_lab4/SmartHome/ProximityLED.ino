#include "Adafruit_VCNL4200.h"  // Include library for VCNL4200 sensor
#include <SPI.h>  // Include SPI library
#include <Wire.h>  // Include Wire library for I2C communication
#include "Adafruit_MCP23008.h"  // Include library for MCP23008 GPIO expander

// Create instances of the VCNL4200 and MCP23008 objects
Adafruit_MCP23008 mcp_leds;
Adafruit_VCNL4200 vcnl4200;

void initializeProximity() {
  // Set up the serial communication with baud rate of 115200
  Serial.swap(3);  // Swap the TX/RX pins if needed (platform-specific)
  Serial.begin(115200);  // Initialize serial communication

  // Initialize the VCNL4200 sensor, check if it's connected properly
  if (!vcnl4200.begin()) {
    Serial.println("Could not find a valid VCNL4200 sensor, check wiring!");  // Print error if sensor is not found
    while (1) {
      delay(10);  // Wait in an infinite loop if the sensor is not found
    }
  }

  // Configure the VCNL4200 sensor settings
  vcnl4200.setALSshutdown(true);  // Shut down ambient light sensor (ALS)
  vcnl4200.setProxShutdown(false);  // Enable proximity sensor
  vcnl4200.setProxHD(false);  // Set proximity sensor high-definition mode off
  vcnl4200.setProxLEDCurrent(VCNL4200_LED_I_200MA);  // Set proximity LED current
  vcnl4200.setProxIntegrationTime(VCNL4200_PS_IT_8T);  // Set proximity integration time

  uint8_t pin_id, status;

  // Initialize MCP23008 GPIO expander at I2C address 0x25
  status = mcp_leds.begin(0x25);  

  // Set all 8 GPIO pins of MCP23008 as output and turn off LEDs initially
  for (pin_id = 0; pin_id < 8; pin_id++) {
    mcp_leds.pinMode(pin_id, OUTPUT);  // Set each pin as output
    mcp_leds.digitalWrite(pin_id, HIGH);  // Set the pin to HIGH (turn off LED)
  }
}

void proximityLoop() {
  // Read proximity data from the VCNL4200 sensor
  uint16_t proxData = vcnl4200.readProxData();  
  Serial.print("Prox Data: ");  // Print proximity data to serial monitor
  Serial.println(proxData);  
  LEDs(proxData);  // Call the LEDs function to update LED states based on proximity data
  delay(100);  // Wait 100 milliseconds before the next loop
}

void LEDs(uint16_t proxData) {
  static unsigned long prox_timer = 0UL;  // Timer variable to control LED effect timing
  unsigned long now;

  now = millis();  // Get the current time in milliseconds
  if (now - prox_timer > 200UL) {  // If 200ms has passed since last update
    prox_timer = now;  // Update the timer value

    // Map the proximity data to the number of LEDs to light up
    uint8_t numLEDs = map(proxData, 0, 4095, 0, 8); 

    // Loop through each of the 8 LEDs and turn on/off based on the number of lit LEDs
    for (uint8_t i = 0; i < 8; i++) {
      if (i < numLEDs) {
        mcp_leds.digitalWrite(i, LOW);  // Turn on the LED (LOW is on for MCP23008)
      } else {
        mcp_leds.digitalWrite(i, HIGH);  // Turn off the LED (HIGH is off for MCP23008)
      }
    }
  }
}
