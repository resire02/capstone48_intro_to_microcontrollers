## Requirements
In this lab, we will bring together everything we've covered so far into one comprehensive project: a home monitoring and automation system. Unlike previous labs, this one will focus on integrating various components into a single project. Below, you'll find the requirements that your project and code need to meet. At the end of the lab, we will review a solution that satisfies all the requirements.
# Goals:

1. The first requirement is to read temperature data from the MCP9808 temperature sensor on the board.
2. Based on the temperature value read from the sensor, adjust the color of the RGB LED. The LED should transition from blue (cold) to red (hot), depending on the temperature.

### Door Bell
3. When the middle (SW2) touch button (MTCH1030) is pressed, play a sound similar to a door bell.
4. The code for the door bell should not delay the loop function. (Hint: remember how the `millis()` function was used back in lab 1)
