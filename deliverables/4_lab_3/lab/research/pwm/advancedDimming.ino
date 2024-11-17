#include "Dx_PWM.h"  // Include the Dx_PWM library to handle PWM functionality on multiple pins

#define SerialDebug   Serial

// Define an array of pins where the RGB LED is connected (PD1, PD2, PD3 for red, green, blue)
uint32_t PWM_Pins[] = { PIN_PD1, PIN_PD2, PIN_PD3 };

// Define the number of PWM pins (for RGB LED, there are 3 pins)
#define NUM_OF_PINS   ( sizeof(PWM_Pins) / sizeof(uint32_t) )

// Create an array of PWM instances for controlling each pin
Dx_PWM* PWM_Instance[NUM_OF_PINS];

// String to separate output in the Serial Monitor for better readability
char dashLine[] = "======================================";

// Function to print detailed PWM information for each pin
void printPWMInfo(Dx_PWM* PWM_Instance)
{
  SerialDebug.println(dashLine);  // Print a line for separation
  SerialDebug.print("Actual data: pin = ");
  SerialDebug.print(PWM_Instance->getPin());  // Print the current pin
  SerialDebug.print(", PWM DC = ");
  SerialDebug.println(PWM_Instance->getActualDutyCycle());  // Print the current duty cycle (PWM brightness)
  SerialDebug.println(dashLine);  // Print a line for separation
}

void setup()
{
  // Set up the PORTMUX to route the TCA (Timer/Counter A) to Port D, enabling PWM on pins PD1, PD2, PD3
  PORTMUX.TCAROUTEA = PORTMUX_TCA0_PORTD_gc;

  // Initialize the Serial communication for debugging
  SerialDebug.swap(3);  // Swap UART (necessary for correct serial output)
  SerialDebug.begin(115200);  // Start the serial communication at 115200 baud rate

  // Initialize each PWM pin and create an instance of the Dx_PWM object for each pin
  for (uint8_t index = 0; index < NUM_OF_PINS; index++)
  {
    pinMode(PWM_Pins[index], OUTPUT);  // Set each PWM pin as an output
    PWM_Instance[index] = new Dx_PWM(PWM_Pins[index], 100.0f, 100.0f);  // Create a new Dx_PWM instance for each pin.
  }
}

void loop()
{
  // Gradually increase the duty cycle (brightness) of the LED from a low value (6656) to a high value (58880)
  // 6656 is chosen as the nearest multiple of 256 to 10% of 65536, and 58880 is calculated as 65536 - 6656,
  // representing 90% brightness, with both values being multiples of 256 for better control resolution.
  for (uint16_t j = 6656; j <= 58880; j += 6656) {
    // Loop through each PWM pin (PD1, PD2, PD3)
    for (uint8_t index = 0; index < NUM_OF_PINS; index++) {
      // Convert the value `j` to a percentage for the duty cycle
      float dutyCycle = (j / (float)65536) * 100.0;

      // Set the duty cycle for the current pin
      PWM_Instance[index]->setPWM(PWM_Pins[index], 100.0f, dutyCycle);

      // Delay for 10 milliseconds
      delay(10);

      // Print the current PWM information to the Serial Monitor
      printPWMInfo(PWM_Instance[index]);
    }
  }

  // Gradually decrease the duty cycle (brightness) of the LED from the high value (58880) back to the low value (6656)
  for (uint16_t j = 58880; j >= 6656; j -= 6656) {
    // Loop through each PWM pin (PD1, PD2, PD3)
    for (uint8_t index = 0; index < NUM_OF_PINS; index++) {
      // Convert the value `j` to a percentage for the duty cycle
      float dutyCycle = (j / (float)65536) * 100.0;

      // Set the duty cycle for the current pin
      PWM_Instance[index]->setPWM(PWM_Pins[index], 100.0f, dutyCycle);

      // Delay for 10 milliseconds
      delay(10);

      // Print the current PWM information to the Serial Monitor
      printPWMInfo(PWM_Instance[index]);
    }
  }
}