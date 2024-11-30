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

# Door Bell Walkthrough
Objective: Implement a functioning doorbell using PWM and capacitive touch sensor in the middle.

Implementing a door bell is slightly challenging since we cannot use delay functions as it would interfere with other code in the loop function.
The door bell consists of two parts: reading input from the capacitive touch sensor and playing notes on the speaker using PWM.
First, we need to import the Dx_PWM library and setup the speaker and capacitive touch pins. We will also use an external file for the notes.
```
#include <Dx_PWM.h>
#include "notes.h"

#define DOOR_BELL PIN_PC2
#define SPEAKER_PIN PIN_PD2
```

Before the setup function, we set up doorbell tones and declare a note duration:
```
#define NOTE_PERIOD 750
#define DOOR_NOTES_COUNT 2
float door_notes[] = {NOTE_A6S, NOTE_F6S};
```

We will also need to initialize the Dx_PWM class to play notes through PWM.
```
Dx_PWM* speaker;
``` 

In the setup function, we will need to set the pinModes for the pins and reroute the PWM timer.
```
void setup() {
  pinMode(DOOR_BELL, INPUT);
  pinMode(SPEAKER_PIN, OUTPUT);
  
  PORTMUX.TCAROUTEA = PORTMUX_TCA0_PORTD_gc;
  speaker = new Dx_PWM(SPEAKER_PIN, 1000.0f, 0.0f);
}
```

In the loop function, we will setup the following code:
```
void loop() {
  static int speaker_index = -1;
  static uint16_t speaker_timer = 0;
  uint16_t now = millis();

  if (speaker_index != -1 && now - speaker_timer > NOTE_PERIOD) {
    speaker_timer = now;
    speaker_index++;
    if (speaker_index < DOOR_NOTES_COUNT) {
      speaker->setPWM(SPEAKER_PIN, door_notes[speaker_index], 0.0f);
    } else {
      speaker_index = -1;
      speaker->setPWM(SPEAKER_PIN, 0.0f, 0.0f);
    }
  }

  bell_value = digitalRead(DOOR_BELL);
  if (bell_value == LOW && speaker_index == -1) {
    speaker_index = 0;
    speaker->setPWM(SPEAKER_PIN, door_notes[speaker_index], 0.0f);
    speaker_timer = now;
  }
}
```

In the beginning part of the loop function, we set up a few static (meaning consistent between function runs) variables to store the speaker index, which is used to track which note is being played, and the speaker timer, which is used to track when the speaker should move on the next note. The speaker index is set to -1 as a default state to indicate that it is not playing.
In the first if statement, it is checking if the speaker is not playing and checks if the time (note period) since the last note has passed already. When these conditions are met, the speaker timer is updated to the current time, effectively resetting the timer.
Then, the speaker index is incremented and checked if all notes have been played. If all notes have not been played (ie. not at the end of the note array), then we will continue on to the next note.

In the second half, we read the value from the capacitive touch sensor. When the sensor is being pressed, the value is LOW so we check in the if statement if the sensor is being pressed and that the speaker is not already playing.
Then, the speaker index is updated to 0 and the first note is played from the note array.

The capacitive touch sensor and speaker need to be connected via pin remapping, so we will reroute PIN_PC3 to the capacitive touch button's TS4 sensor pin and the PIN_PD2 to the AMP_IN pin to the right of the speaker.