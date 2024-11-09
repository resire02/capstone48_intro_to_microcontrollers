/* This sketch is based on sample sketches available at the Dx_PWM repo
   analogWrite() does not support writing multiple PWM outputs on the same RGB LED
   You can do it with Dx_PWM!
   This sketch intensifies and fades a white light on the RGB LED.
 */

#include "Dx_PWM.h"

uint32_t PWM_Pins[] = { PIN_PD1, PIN_PD2, PIN_PD3 };
#define SerialDebug   Serial
#define NUM_OF_PINS   ( sizeof(PWM_Pins) / sizeof(uint32_t) )

Dx_PWM* PWM_Instance[NUM_OF_PINS];

char dashLine[] = "=====================================================================================";

void printPWMInfo(Dx_PWM* PWM_Instance)
{
  SerialDebug.println(dashLine);
  SerialDebug.print("Actual data: pin = ");
  SerialDebug.print(PWM_Instance->getPin());
  SerialDebug.print(", PWM DC = ");
  SerialDebug.print(PWM_Instance->getActualDutyCycle());
  SerialDebug.print(", PWMPeriod = ");
  SerialDebug.print(PWM_Instance->getPWMPeriod());
  SerialDebug.print(", PWM Freq (Hz) = ");
  SerialDebug.println(PWM_Instance->getActualFreq(), 4);
  SerialDebug.println(dashLine);
}

void setup()
{
  // this is required to route the TCA to Port D and enable PWM on pins PD1 to PD3
  PORTMUX.TCAROUTEA = PORTMUX_TCA0_PORTD_gc;
  SerialDebug.swap(3);
  SerialDebug.begin(115200);
  for (uint8_t index = 0; index < NUM_OF_PINS; index++)
  {
    pinMode(PWM_Pins[index], OUTPUT);
    PWM_Instance[index] = new Dx_PWM(PWM_Pins[index], 100.0f, 100.0f);
  }
}

void loop()
{
  for (uint16_t j = 6656; j <= 58880; j += 6656) {
    for (uint8_t index = 0; index < NUM_OF_PINS; index++) {
      float dutyCyclePercentage = (j / (float)65536) * 100.0; // Convert to percentage
      PWM_Instance[index]->setPWM(PWM_Pins[index], 100.0f, dutyCyclePercentage);
      printPWMInfo(PWM_Instance[index]);
    }
  }

  for (uint16_t j = 58880; j >= 6656; j -= 6656) {
    for (uint8_t index = 0; index < NUM_OF_PINS; index++) {
      float dutyCyclePercentage = (j / (float)65536) * 100.0; // Convert to percentage
      PWM_Instance[index]->setPWM(PWM_Pins[index], 100.0f, dutyCyclePercentage);
      printPWMInfo(PWM_Instance[index]);
    }
  }

}