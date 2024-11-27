void setup() {
  Serial.swap(3);
  Serial.begin(115200);
  delay(100);
}

void loop() {
  static uint8_t count = 1;
  
  Serial.printf("%d\n", count);
  count++;
  if (count > 10) {
    count = 1;
  }
  delay(1000);
}
