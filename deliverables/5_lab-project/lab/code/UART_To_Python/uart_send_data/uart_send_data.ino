void setup() {
  Serial.swap(3);
  Serial.begin(115200);
  delay(100);
}

void loop() {
  for (int i = 0; i < 8; i++) {
    Serial.printf("Temperature: %d\n", i);
    if (i % 5 == 0)
      Serial.printf("Room: %d Color: Green\n", i);
    else if (i % 3 == 0)
      Serial.printf("Room: %d Color: Blue\n", i);
    else
      Serial.printf("Room: %d Color: Red\n", i);
    delay(2000);
  }
}
