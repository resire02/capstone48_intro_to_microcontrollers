# **Lab 1: Blink an LED\!**

## Required Materials

This lab requires the following materials:

* A desktop or laptop computer  
* Arduino IDE (Go to [https://www.arduino.cc/en/software](https://www.arduino.cc/en/software) if not installed already)  
* DXCore support library  
* AVR64DD32 Curiosity Nano evaluation kit  
* Standard-A to Micro-B cable (or a Micro-AB cable) with data transfer support

Most USB cables support data transfer capabilities; however, if Arduino IDE is unable to locate the board, this usually indicates that the cable does not support data transfer.

## Learning Objectives

This lab is intended to give you an understanding of how to deploy a basic program to your Curiosity Nano board. Along the way, you will learn:

1. How to identify pins on the Curiosity Nano board (and their associated number in code)   
2. A few basic methods common to almost all programs run on the board  
3. How to blink an on board LED.

Throughout this lab, you will gain a greater understanding of how to work with the board through Arduino IDE, deploy code to the Curiosity Nano board, and identify features on the board.  

## The “Sketch” File

A “sketch” file is a **program** that is uploaded onto an Arduino board by Arduino IDE. Sketch files contain **functions**, which are grouped lines of code that can be called from anywhere in the program. A function contains a header, which details the function name and what values it requires, and a body, that details what code should be run when the function is called.  

![sketch functions explanation](./images/sketch-functions-visual-explanation.png)

There are 5 functions that are built into all Arduino sketches:

* **setup** – runs once during program execution  
* **loop** – runs infinitely during program execution  
* **pinMode** – labels a specific pin as a source to read from (input) or as a source to write to (output)  
* **digitalWrite** – tells a pin to use either LOW or HIGH voltage  
* **delay** – tells the sketch to wait a specified number of milliseconds before running the next line

The **setup** and **loop** functions need to be defined with a function body, while the **pinMode**, **digitalWrite**, and **delay** functions can be called without defining a function body. This is because setup and loop are **special functions** that are called by the Arduino program and contain the main functionality of the sketch.

## Lab Setup

1. Go to File \-\> Examples \-\> 01.Basics \-\> Blink  
2. Arduino is based on a language called Wiring. It's basically C++.  
3. The basic functionality of a Microcontroller includes  
   - pinMode()  
     * In Microcontroller space, GPIO pins can be input or output.  
     * In modern ones, they can be both at the same time, which is important for fault tolerance or error checking.  
     * In a general sense, pinMode() sets pin as either input or output  
     * The macro LED\_BUILTIN matches the pin number.  
   - digitalWrite()  
     * This function sets the target to either HIGH or LOW.  
   - delay()  
     * This function takes an argument in milliseconds and waits for that amount of time.

![image info](./images/samplecode.png)

## Loading Code onto Board

1. Ensure your board is connected to a USB port on your computer.
2. In the top left corner of the Arduino IDE, click the dropdown menu next to the three buttons shown in the image below.

![image info](./images/lab1(1).jpg)
   
3. Select “Other Boards and Ports.”
4. Search for and select AVR DD-series (no bootloader) from the list.
5. Choose the appropriate port for your device, typically labeled as COM# Serial Port (USB), where the number sign represents the specific number assigned by your computer. If multiple ports are listed, you can identify the correct one by opening your computer's Device Manager and checking under the Ports section. Refer to the image below for guidance.

![image info](./images/lab1(5).png)
   
6. Once you’ve selected the correct board and port, click OK.
7. Navigate to the Tools tab and verify that the Chip is set to AVR64DD32 and the Programmer is set to Curiosity Nano (nEDBG, debug chip: ATSAMD21E18). If these settings are incorrect, click on each section to select the appropriate chip and programmer. See the image below for reference.

![image info](./images/lab1(7).png)
   
8.Next, click the Verify button (the one with the checkmark) located at the top left corner of the screen. Refer to the image below for visual assistance.

![image info](./images/lab1(8).jpg)
  
9. Finally, click on Sketch in the toolbar and select Upload Using Programmer. This action will download the code to the microcontroller.
