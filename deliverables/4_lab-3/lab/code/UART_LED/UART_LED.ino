# define LED_Pin 25

void setup() { 
  pinMode(LED_Pin, OUTPUT);
  Serial.swap(3);
  Serial.begin(115200);
  delay(100);
  Serial.println("Enter on or off.");
}

void loop() {
 if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');  
    input.trim(); 

    if (input.equalsIgnoreCase("on")) {  
      digitalWrite(LED_Pin, LOW);       
      Serial.println("LED is ON");
    } else if (input.equalsIgnoreCase("off")) { 
      digitalWrite(LED_Pin, HIGH);        
      Serial.println("LED is OFF");
    } else {
      Serial.println("Invalid input. Type 'on' or 'off'."); 
    }
  }
}
