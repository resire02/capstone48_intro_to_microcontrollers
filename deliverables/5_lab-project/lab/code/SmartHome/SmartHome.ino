void setup() {
  initializePassword();
  initializeRoom();
  initializeTemperature();
  initializeDoorBell();
  initializeProximity();
}

void loop() {
  roomLoop();
  temperatureLoop();
  doorBellLoop();
  proximityLoop();
}