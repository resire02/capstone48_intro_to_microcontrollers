#include <Wire.h>

// MCP9808 I²C address
#define MCP9808_ADDR 0x1C

// RGB LED pins
const int RED_PIN = 13;    // Adjust to your PWM-capable pin for Red

const int BLUE_PIN = 15;  // Adjust to your PWM-capable pin for Blue

// Temperature range
const float TEMP_MIN = 0.0;   // Minimum temperature for blue
const float TEMP_MAX = 40.0;  // Maximum temperature for red

void setup() {
  Wire.begin(); // Initialize I²C communication
  Serial.swap(3);
  Serial.begin(115200); // Initialize serial communication

  // Initialize RGB pins
  pinMode(RED_PIN, OUTPUT);
 
  pinMode(BLUE_PIN, OUTPUT);

  // Initialize MCP9808 sensor
  Wire.beginTransmission(MCP9808_ADDR);
  Wire.write(0x01); // Access config register
  Wire.write(0x00); // Continuous conversion mode
  Wire.write(0x00);
  Wire.endTransmission();
}

void loop() {
  float temperature = readTemperature();
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  // Update LED color based on temperature
  updateLEDColor(temperature);
  
  delay(1000); // Delay 1 second
}

float readTemperature() {
  Wire.beginTransmission(MCP9808_ADDR);
  Wire.write(0x05); // Temperature register
  Wire.endTransmission();

  // Request 2 bytes of data from the sensor
  Wire.requestFrom(MCP9808_ADDR, 2);
  byte msb = Wire.read();
  byte lsb = Wire.read();

  // Combine the bytes and process the temperature
  int temp = ((msb & 0x1F) << 8) | lsb;
  if (msb & 0x10) {  // Check sign bit
    temp -= 4096;
  }
  return temp * 0.0625; // Convert to °C
}

void updateLEDColor(float temperature) {
  // Clamp temperature to the range of TEMP_MIN to TEMP_MAX
  if (temperature < TEMP_MIN) temperature = TEMP_MIN;
  if (temperature > TEMP_MAX) temperature = TEMP_MAX;

  // Calculate the color interpolation factor (0.0 to 1.0)
  float factor = (temperature - TEMP_MIN) / (TEMP_MAX - TEMP_MIN);

  // Calculate RGB values (blue to red)
  int redValue = int(factor * 255);   // From 0 (cold) to 255 (hot)
  int blueValue = int((1 - factor) * 255); // From 255 (cold) to 0 (hot)
 
  Serial.print("Red");
  Serial.println(redValue);
  Serial.print("Blue");
  Serial.println(blueValue);
  // Set the RGB LED using PWM
  analogWrite(RED_PIN, redValue);
  analogWrite(BLUE_PIN, blueValue);
  delay(1000);
}
