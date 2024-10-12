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
