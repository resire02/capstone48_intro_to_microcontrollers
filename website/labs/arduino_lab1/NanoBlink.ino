# define LED_Pin 25

// The setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_Pin, OUTPUT);
}

// The loop function runs over and over again
void loop() {
  digitalWrite(LED_Pin, HIGH);  // Turn the LED off
  delay(1000);                      // wait for a second
  digitalWrite(LED_Pin, LOW);   // turn the LED on
  delay(1000);                      // wait for a second
}