## Requirements
In this lab, we will bring together everything we've covered so far into one comprehensive project: a home monitoring and automation system. Unlike previous labs, this one will focus on integrating various components into a single project. Below, you'll find the requirements that your project and code need to meet. At the end of the lab, we will review a solution that satisfies all the requirements.

# Goals:

### Smart Lock with Password
1. The system shall accept a user-entered password, compare it against a stored password, and grant access to the smart 
home entry if the passwords match, or deny access if they do not match.
2. The system shall display password input on the OLED screen.
3. The system shall print "Password found" when a password is found and "No password found" when a password is not found
4. The system shall print "Try again" when the inputted password does not match the password in the EEPROM

### Door Bell
1. When the joystick is pressed down, play a sound similar to a doorbell.
2. The code for the doorbell should not delay the loop function. (Hint: remember how the `millis()` function was used back in lab 1)

### Temperature Sensor
1. The first requirement is to read temperature data from the MCP9808 temperature sensor on the board.
2. Based on the temperature value read from the sensor, adjust the color of the RGB LED. The LED should transition from blue (cold) to red (hot), depending on the temperature.
3. The temperature sensor should print the temperature in the following format: "Temperature: 30 °C"

### Smart Lighting
1. When the leftmost button (SW1) is pressed, LED should turn blue.
2. When the middle button (SW2) is pressed, LED should turn green.
3. When rightmost button (SW3) is pressed, LED should turn red.
4. Temp state should be maintained for each of the 8 "rooms" (LEDs that form the neo pixel LED ring), at least while board is plugged in (not between deployments). 
5. Default color state is blue
6. When changing the color of the room, the program should print "changing room color to <color>"


### Room Selector
1. When potentiometer is turned, the light should change accordingly (scaling 1-8 for lowest vs highest point of potentiometer)
2. Light color should match that of the color selected from smart lighting (default is blue)
3. When changing the room, the program should print "moving to room <room> with color <color>" where the room is the index of the lit LED and color is the name of the color of the LED (blue, green, red).

### Joystick
1. Joy stick should retrieve input from all 4 directions (up, down, left, right) and additionally pressing in

### Distance Sensor

1. Read data from the distance sensor VCNL4200.
2. Based of the data from the distance sensor make the Amber LEDS light up so that the closer an object is to the distance sensor the more LEDs light up.
3. The program should print the proximity in the following format: "proximity: <value>" where value is the proximity value from the distance sensor.