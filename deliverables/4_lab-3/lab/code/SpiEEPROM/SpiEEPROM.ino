#include <EEPROM.h>

const int PAGE_SIZE = EEPROM.length();

void setup() {
  Serial.swap(3);         // swtich to correct ports
  Serial.begin(115200);   // start communication on 115200 baud
  while (!Serial);        // wait for Serial to ready

  int index, read_value;

  // write numbers 1 to 10
  Serial.println(F("Writing numbers from 1 to 10 to the first 10 cells!"));
  for (index = 0; index < 10; index++) {
    EEPROM.update(index, index + 1);
  }

  // read numbers 1 to 10
  Serial.print("[ ");
  for (EEPtr ptr = 0; ptr.index < 10; ptr++) {
    read_value = *ptr;
    Serial.printf("%d, ", read_value);
  }
  Serial.print("]\n");

  // update the numbers to their square
  Serial.println(F("Squaring the first 10 cells!"));
  for (index = 0; index < 10; index++) {
    EEPROM.get(index, read_value);
    EEPROM.update(index, read_value * read_value);
  }

  // read numbers 1 to 10
  Serial.print("[ ");
  for (EEPtr ptr = 0; ptr.index < 10; ptr++) {
    read_value = *ptr;
    Serial.printf("%d, ", read_value);
  }
  Serial.print("]\n");

  Serial.println(F("Done!"));
}

void loop() {
  
}
