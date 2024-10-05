# Self Learning Evaluation

#### Capstone Member:	Gonzalo Allendes  
#### Sprint Name:		Getting Started  
#### Link to Taiga Task:	[Task 7](https://tree.taiga.io/project/bookstrong-introduction-to-microcontroller/task/7)
#### Sprint Topic:		Arduino Setup

---

### Document your research in this section

- This is an outline of the most important knowledge gathered from meeting #2:

```
1. Installation Walkthrough as Documented in Sponsor (0:00 - 14:00)

    1. Go to the Arduino Software page (URL: https://www.arduino.cc/en/software).
    2. Download and run the MSI Installer (Windows).
    3. The IDE should be immediately installed. Run it and allow it some time to install dependencies.
    4. Please go to File -> Preferences and under the Settings tab, check 'compile' and 'upload' to enable verbose output.
    5. Under the same tab, click on the icon next to 'Additional Board Manager URLs'
    6. Copy and paste the following URL into the text box and click OK. http://drazzy.com/package_drazzy.com_index.json [1]
    7. Go to the Board Manager by clicking on the second icon from top to bottom on the left panel.
    8. Type 'DxCore' and click INSTALL. This installs the primary support package. [2]

    [1] Enables access to external microcontroller libraries not included in the default setup.  
    [2] Arduino had general libraries to support sensors, but as vendors started making boards,
    board-specific libraries became an independent category of libraries known as core libraries.

2. Quick Tour of the Source Files (14:00 - 21:00)

    1. Open File Explorer. Go to C:\Users\{YourUsername}
    2. Show hidden files (See Appendix) and go to AppData\Local\Arduino15\packages\DxCore\hardware\megaavr\1.5.11
    3. This directory is the collection of C, C++, assembly, and header files that support the AVR Dx microcontroller panel.  
    4. Go to cores\dxcore.
    5. Open wiring.c with the IDE of your preference. 
    6. In wiring.c you fill find an implementation of the Wiring API specifically designed for the AVR Dx microcontrollers.
    7. Check out the millis() function!

    Necessary Appendix
    
        Instructions to show hidden files in Windows:
    
        1. Click three dots in the toolbar
        2. Select Options from the dropdown menu
        3. In the Folder Options window, go to the View tab
        4. Scroll down and select Show hidden files, folders, and drives under 'Advanced settings'

3. Sample Code (21:00 - 29:00)

    1. Go to File -> Examples -> 01.Basics -> Blink
    2. Arduino is based on a language called Wiring. It's basically C++.
    3. In a sketch, there are two primary functions.
        a. setup()
        b. loop()
    4. The premise behind Arduino sketches is calling setup() once, and loop() to start an infinite loop.
    5. Basic functionality of a Microcontroller includes
        a. pinMode()
            - In Microcontroller space, GPIO pins can be input or output.
            - In modern ones, they can be both at the same time, which is important for fault tolerance or error checking.
            - In general sense, pinMode() sets pin as either input or output
            - The macro LED_BUILTIN matches pin number.
        b. digitalWrite()
            - Sets target to either HIGH or LOW.
        c. delay()
            - Takes an argument in milliseconds.

4. General (29:00 - 31:00)

    1. If you can get someone to get an LED to blink in 5 minutes, they will stick with that development system.
    2. First Introduction: Getting IDE and DXCore installed with what a sketch looks like, setup(), loop(), basic descriptors. (30:00) 

5. Summary of AVR64DD32 (31:00 - 44:47)

    1. The Curiosity Nano Board is a common form factor on low cost eval tools.
    2. Diamond shaped square is the microcontroller and it has 64 bytes of flash.
    3. Targeted as an upscale to the Mega328P. Has twice the memory and extra peripherals.
    4. Some of the peripherals have improved accuracy and more functions.
    5. Has a switch and onboard debugger that sets breakpoints.
    6. There is a USB to serial converter on the debugger's side of the board.
    7. Please solder the pins.
    8. Additionally, this family of microcontrollers is one of the first ones to support two different voltage rails
    on its pins. Many industrial things are still in 5V, but a lot of the Bluetooth modules are in 3.3V. This
    board has voltage translators.

```

### What went well during the learning process?

- Our sponsor's initial presentation was well-structured and clear. 

### Were there any topic(s) that were difficult to understand during the learning process?

- Source code files are challenging to read and analyze (wiring.c).
- Initial sample code should be easily understood by anyone with a basic knowledge of programming languages.

### What troubles/issues did you encounter while working with the Arduino system?

- No major difficulties were encountered while following the installation walkthrough or visiting the required files.

### If you encountered any issues while working with Arduino, were you able to fix them? If so, what steps did you take to fix the issues you encountered?

- No issues were encountered while working on this section.