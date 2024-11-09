/*
  This is an adaptation of the sample sketch at
  File -> Examples -> 03.Analog -> AnalogInOutSerial

  Reads an analog input pin, maps the result to a range from 0 to 255 and uses
  the result to set the pulse width modulation (PWM) of an output pin.
  Also prints the results to the Serial Monitor.
*/

// These constants won't change. They're used to give names to the pins used:
const int analogInPin = PIN_PD7;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = PIN_PD1;  // Analog output pin that the LED is attached to

int sensorValue = 0;  // value read from the pot
int outputValue = 0;  // value output to the PWM (analog out)

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.swap(3);
  Serial.begin(115200);
  // this is required to route the TCA to Port D and enable PWM on pins PD1 to PD3
  PORTMUX.TCAROUTEA = PORTMUX_TCA0_PORTD_gc;
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 254);
  // change the analog out value:
  analogWrite(analogOutPin, outputValue);

  // print the results to the Serial Monitor:
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.println(outputValue);

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(2);
}
