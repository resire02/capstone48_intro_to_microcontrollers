void setup() {
  initializePassword();
  initializeRoom();
  initializeTemperature();
  initializeDoorBell();
}

void loop() {
  roomLoop();
  temperatureLoop();
  doorBellLoop();
}