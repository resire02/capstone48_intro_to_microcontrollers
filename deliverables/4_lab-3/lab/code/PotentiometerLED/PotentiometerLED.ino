#define POTMETERPIN 19

#include <Wire.h>
#include "Adafruit_MCP23008.h"

Adafruit_MCP23008 mcp_leds;

void setup() {
  // put your setup code here, to run once:
  Serial.swap(3);
  Serial.begin(115200);

  uint8_t pin_id, status;

  status = mcp_leds.begin(0x25);

  for (pin_id = 0; pin_id < 8; pin_id++) {
    mcp_leds.pinMode(pin_id, OUTPUT);
    mcp_leds.digitalWrite(pin_id, HIGH);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  int readValue = analogRead(POTMETERPIN);
  int leds = 0;

  Serial.println("Potmeter value: " + String(readValue));

  while(readValue > 128) {
    readValue = readValue - 128; 
    leds++;
  }

  for(int i = 0; i < 8; i++){
    if(i <= leds){
      mcp_leds.digitalWrite(7-i, LOW);
    } else {
      mcp_leds.digitalWrite(7-i, HIGH);
    }
  }
}
