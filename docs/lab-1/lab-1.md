## Sample Code and Basic Functions

1. Go to File \-\> Examples \-\> 01.Basics \-\> Blink  
2. Arduino is based on a language called Wiring. It's basically C++.  
3. In a sketch, there are two primary functions.  
   * setup()  
   * loop()  
4. The premise behind Arduino sketches is calling setup() once, and loop() to start an infinite loop.  
5. The basic functionality of a Microcontroller includes  
   * pinMode()  
     1. In Microcontroller space, GPIO pins can be input or output.  
     2. In modern ones, they can be both at the same time, which is important for fault tolerance or error checking.  
     3. In general sense, pinMode() sets pin as either input or output  
     4. The macro LED\_BUILTIN matches pin number.  
   * digitalWrite()  
     1. Sets target to either HIGH or LOW.  
   * delay()  
     1. Takes an argument in milliseconds.

![image info](./images/samplecode.png)