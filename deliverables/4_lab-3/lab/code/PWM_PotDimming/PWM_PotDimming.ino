const int analogInPin = PIN_PD7;  // Analog input pin where the potentiometer is connected
const int analogOutPin = PIN_PD1;  // Analog output pin where the LED (RGB) is connected

int sensorValue = 0;  // Variable to store the value read from the potentiometer
int outputValue = 0;  // Variable to store the mapped PWM value for controlling LED brightness

void setup() {
  // Initialize serial communication at 115200 baud rate
  Serial.swap(3);  // Swap UART for serial communication
  Serial.begin(115200);  // Start serial communication

  // Set up the port multiplexer to route the PWM signal to Port D
  // This enables PWM output on pins PD1 to PD3
  PORTMUX.TCAROUTEA = PORTMUX_TCA0_PORTD_gc;
}

void loop() {
  // Read the analog value from the potentiometer (range: 0 to 1023)
  sensorValue = analogRead(analogInPin);

  // Map the sensor value (0-1023) to the PWM range (0-254)
  // PWM has a range of 0-255, but 254 is used to avoid full duty cycle
  outputValue = map(sensorValue, 0, 1023, 0, 254);

  // Write the mapped PWM value to the output pin, adjusting LED brightness
  analogWrite(analogOutPin, outputValue);

  // Print the sensor value and the corresponding PWM output value to the Serial Monitor
  // Helps in debugging and observing the effect of the potentiometer
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.println(outputValue);

  // Wait for 2 milliseconds to allow the analog-to-digital converter to settle before the next reading
  delay(2);
}