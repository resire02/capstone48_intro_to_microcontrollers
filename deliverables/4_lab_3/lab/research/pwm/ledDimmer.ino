#include "Dx_PWM.h"

uint32_t PWM_Pins[] = { PIN_PD1, PIN_PD2, PIN_PD3 };
#define SerialDebug   Serial
#define NUM_OF_PINS   ( sizeof(PWM_Pins) / sizeof(uint32_t) )

Dx_PWM* PWM_Instance[NUM_OF_PINS];

float frequency[]   = { 100.0f,
                        100.0f,
                        100.0f};

float dutyCycle[]   = { 50.0f,
                        50.0f,
                        50.0f};

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
  PORTMUX.TCAROUTEA = PORTMUX_TCA0_PORTD_gc;
  SerialDebug.swap(3);
  SerialDebug.begin(115200);
  for (uint8_t index = 0; index < NUM_OF_PINS; index++)
  {
    PWM_Instance[index] = new Dx_PWM(PWM_Pins[index], frequency[index], dutyCycle[index]);
  }
}

void loop()
{
  for (uint8_t index = 0; index < NUM_OF_PINS; index++) {
    PWM_Instance[index]->setPWM(PWM_Pins[index], frequency[index], dutyCycle[index]);
    printPWMInfo(PWM_Instance[index]);
  }

  delay(1000);

  for (uint8_t index = 0; index < NUM_OF_PINS; index++) {
    PWM_Instance[index]->setPWM(PWM_Pins[index], frequency[index], dutyCycle[index]/3);
    printPWMInfo(PWM_Instance[index]);
  }

  delay(1000);
}