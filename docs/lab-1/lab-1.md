# **Quick Start Guide**

## Required Materials

This lab requires the following materials:

* A desktop or laptop computer  
* Arduino IDE (Go to [https://www.arduino.cc/en/software](https://www.arduino.cc/en/software) if not installed already)  
* DXCore support library  
* AVR64DD32 Curiosity Nano evaluation kit  
* A Standard-A to Micro-B cable (or a Micro-AB cable) with data transfer support

Most USB cables support data transfer capabilities; however, if Arduino IDE is unable to locate the board, this usually indicates that the cable does not support data transfer.

## Learning Objectives

This lab is intended to give you an understanding of how to deploy a basic program to your Curiosity Nano board. Along the way, we will learn:

1. How to identify pins on the Curiosity Nano board (and their associated number in code)   
2. A few basic methods common to almost all programs run on the board  
3. How to blink an on board LED.

Through this lab, you will gain a greater understanding of how to interact with the board through code, deploy code to the board, and identify pins and peripherals on the board.  

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

## Loading Code onto Board

1. Ensure your board is connected to a USB port on your computer.
2. In the top left corner of the Arduino IDE, click the dropdown menu next to the three buttons shown in the image below.

   ![image info](docs/lab-1/images/lab1(1).jpg)
   
3. Select “Other Boards and Ports.”
4. Search for and select AVR DD-series (no bootloader) from the list.
5. Choose the appropriate port for your device, typically labeled as COM# Serial Port (USB), where the number sign represents the specific number assigned by your computer. If multiple ports are listed, you can identify the correct one by opening your computer's Device Manager and checking under the Ports section. Refer to the image below for guidance.

  ![image info](docs/lab-1/images/lab1(5).png)
   
6. Once you’ve selected the correct board and port, click OK.
7. Navigate to the Tools tab and verify that the Chip is set to AVR64DD32 and the Programmer is set to Curiosity Nano (nEDBG, debug chip: ATSAMD21E18). If these settings are incorrect, click on each section to select the appropriate chip and programmer. See the image below for reference.

  ![image info](docs/lab-1/images/lab1(7).png)
   
8.Next, click the Verify button (the one with the checkmark) located at the top left corner of the screen. Refer to the image below for visual assistance.

  ![image info](docs/lab-1/images/lab1(8).png)
  
9. Finally, click on Sketch in the toolbar and select Upload Using Programmer. This action will download the code to the microcontroller.
