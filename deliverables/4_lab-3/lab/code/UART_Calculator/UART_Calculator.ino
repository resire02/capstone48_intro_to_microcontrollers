void setup() { 
  Serial.swap(3);
  Serial.begin(115200);
  Serial.println("Enter an expression (e.g., 5+3):");
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');  // Read the input until newline
    float num1 = 0, num2 = 0;
    char op;
    bool operatorFound = false;

    // Parse the input
    int i = 0;
    while (i < input.length()) {
      char c = input[i];
      
      if (isdigit(c)) {
        if (!operatorFound) {
          num1 = num1 * 10 + (c - '0');
        } else {
          num2 = num2 * 10 + (c - '0');
        }
      } else {
        op = c;  // Store the operator
        operatorFound = true;
      }
      i++;
    }

    // Check if an operator was found and perform the calculation
    if (operatorFound) {
      switch (op) {
        case '+':
          Serial.println(num1 + num2);
          break;
        case '-':
          Serial.println(num1 - num2);
          break;
        case '*':
          Serial.println(num1 * num2);
          break;
        case '/':
          if (num2 != 0) {
            Serial.println(num1 / num2);
          } else {
            Serial.println("Error: Division by zero");
          }
          break;
        default:
          Serial.println("Invalid operator");
      }
    } else {
      Serial.println("Invalid expression format");
    }
  }
}
