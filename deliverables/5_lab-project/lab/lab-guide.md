## Lab Walk Through

# Code Walkthrough for MCP9808 Temperature Sensor with RGB LED

Objective
This program demonstrates how to read temperature data from the MCP9808 sensor via I²C communication and visualize it using an RGB LED. The LED color transitions smoothly from blue (indicating cold) to red (indicating hot) based on the temperature range.

Include the necessary library for I²C communication:

    #include <Wire.h>

The Wire.h library is essential for establishing I²C communication between the Curiosity Nano and the MCP9808 temperature sensor.
Define the I²C address of the MCP9808 temperature sensor:

    #define MCP9808_ADDR 0x1C

The sensor's default I²C address (0x1C) is stored as a constant for convenience.
Assign pins for the RGB LED and define the temperature range:

    const int RED_PIN = 13;   // Pin for red LED
    const int BLUE_PIN = 15;  // Pin for blue LED
    const float TEMP_MIN = 0.0;   // Minimum temperature for blue
    const float TEMP_MAX = 40.0;  // Maximum temperature for red

These constants set up the hardware configuration and specify the temperature range for color interpolation.
Setup Function
Initialize I²C and UART Communication:

    void setup() {
      Wire.begin(); // Initialize I²C communication
      Serial.swap(3);
      Serial.begin(115200); // Initialize UART communication
    }

Wire.begin() sets up I²C communication.
Serial.begin(115200) initializes serial communication for debugging purposes. Serial.swap(3) reassigns UART to alternate pins.
Configure the RGB LED Pins:

    pinMode(RED_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);

Sets the red and blue pins as outputs to control the RGB LED.
Set MCP9808 to Continuous Conversion Mode:

    Wire.beginTransmission(MCP9808_ADDR);
    Wire.write(0x01); // Access the configuration register
    Wire.write(0x00); // Set continuous conversion mode
    Wire.write(0x00);
    Wire.endTransmission();

Continuous conversion mode allows the sensor to measure temperature continuously and update its registers with the latest data.
Loop Function
Read Temperature and Update LED Colors:

    void loop() {
      float temperature = readTemperature();
      Serial.print("Temperature: ");
      Serial.print(temperature);
      Serial.println(" °C");
    
      updateLEDColor(temperature); // Adjust the LED based on temperature
      delay(1000); // Delay for 1 second
    }

The loop() function continuously reads the temperature using the readTemperature() function and updates the LED color using the updateLEDColor() function. The delay(1000) ensures the temperature is updated once per second.
Reading Temperature

    float readTemperature() {
      Wire.beginTransmission(MCP9808_ADDR);
      Wire.write(0x05); // Access the temperature register
      Wire.endTransmission();
      
      // Request two bytes of temperature data
      Wire.requestFrom(MCP9808_ADDR, 2);
      byte msb = Wire.read();
      byte lsb = Wire.read();
      
      // Combine and convert the data
      int temp = ((msb & 0x1F) << 8) | lsb; // Extract temperature value
      if (msb & 0x10) { // Check for negative temperatures
        temp -= 4096;
      }
      return temp * 0.0625; // Convert to Celsius
    }

Function Purpose: This function reads the temperature data from the MCP9808 and processes it to return a value in Celsius.
How It Works:
Requests data from the temperature register (0x05).
Reads two bytes and combines them to form the raw temperature value.
Converts the raw value to a temperature in Celsius using the MCP9808's conversion factor (0.0625°C per unit).
Updating the RGB LED

    void updateLEDColor(float temperature) {
      // Clamp temperature to the defined range
      if (temperature < TEMP_MIN) temperature = TEMP_MIN;
      if (temperature > TEMP_MAX) temperature = TEMP_MAX;
      
      // Calculate interpolation factor (0.0 to 1.0)
      float factor = (temperature - TEMP_MIN) / (TEMP_MAX - TEMP_MIN);
      
      // Determine RGB values
      int redValue = int(factor * 255);    // Red intensity increases with temperature
      int blueValue = int((1 - factor) * 255); // Blue intensity decreases with temperature
      
      // Debugging output
      Serial.print("Red: ");
      Serial.println(redValue);
      Serial.print("Blue: ");
      Serial.println(blueValue);
      
      // Update LED color using PWM
      analogWrite(RED_PIN, redValue);
      analogWrite(BLUE_PIN, blueValue);
    }

Function Purpose: This function adjusts the RGB LED color based on the current temperature.
How It Works:
Clamping: Ensures the temperature stays within the defined range (TEMP_MIN to TEMP_MAX).
Interpolation: Calculates a factor to linearly interpolate between the minimum and maximum temperature range.
Color Adjustment: Sets red and blue intensities based on the interpolation factor. Cooler temperatures favor blue, while warmer temperatures favor red.
PWM Control: Sends the calculated values to the LED using analogWrite().
