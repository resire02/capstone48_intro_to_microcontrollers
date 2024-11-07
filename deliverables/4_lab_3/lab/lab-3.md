## UART (Universal Asynchronous Receiver-Transmitter)

UART is a communication protocol that enables serial data exchange between two devices without requiring a clock signal. It allows data to be sent and received asynchronously, meaning that data bits are transmitted sequentially over a single wire. This protocol is commonly used for serial communication with microcontrollers and computers.

In the Curiosity Nano, UART allows the board to connect with a computer through a serial communication interface. The Curiosity Nano has a built-in USB-to-UART converter that translates UART signals into USB signals. When the board is connected to a computer via USB, the computer sees it as a virtual COM port, enabling data transfer through serial communication tools like a terminal emulator. This setup allows you to send data to and receive data from the Curiosity Nano for debugging or data exchange.

## ADC (Analog-To-Digital) Converters

An Analog-To-Digital (ADC) converter is a tool that takes real world reading from a sensor (analog) and converts it into a value that can be understood by a program (digital). 
Generally speaking, analog data comes in through sensors or other peripherals, and is continuous in nature; This meaning that it is not set to certain breakpoint or restrictions like variables in code are, think things like voltage or temperature. In order to translate this continous data into digital data, 'breakpoints' are set in order to determine how to round the continous data to fit the digital version. In the below graph you can see an example of this, where value are simply rounded up or down depending on if the value is equal to the actual breakpoint. 

![ADC example graph](./Images/ADC.jpg)  
(from: [https://www.microcontrollerboard.com/analog-to-digital-converter.html](https://www.microcontrollerboard.com/analog-to-digital-converter.html))

In specific, we can look at the space between 011 and 100. Here, we see that the red line (representing digital) only ever increases after the blue line (representing analog) reaches the dashed line above it, even though the blue line is in between 011 and 100. While different Analog-To-Digital converters can interpret these breakpoints differently, especially depending on what is being digitized, the general idea of rounding based on breakpoints remains consistent. 

To further understand this concept, we will be using the on board potentiometer on the Curiosity Nano Explorer board, pictured below. 

![Curiosity Nano Explorer Potentiometer](./Images/Potentiometer.jpg)


