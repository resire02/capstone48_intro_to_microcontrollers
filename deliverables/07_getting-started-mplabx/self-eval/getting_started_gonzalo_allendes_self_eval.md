# Self Learning Evaluation

### Capstone Member: Gonzalo Allendes

### Sprint Name: Getting Started with MPLABX

### Link to Taiga Task: [Task 203](https://tree.taiga.io/project/bookstrong-introduction-to-microcontroller/task/203?)

### Sprint Topic: MPLABX IDE Overview and Setup

---

### Document your research in this section

This is an outline of my findings as I researched sample projects for the AVR64DD32 with MPLABX:

- I searched for sample projects created with MPLABX for the AVR64DD32 and found them [here](https://github.com/orgs/microchip-pic-avr-examples/repositories?q=avr+dd). They are repositories from a Github page called [Microchip PIC & AVR Examples](https://github.com/microchip-pic-avr-examples).
- After exploring various projects, I successfully compiled and ran two of them:
    - [Real-Time Counter in Three Different Modes Using the AVR64DD32 Microcontroller Generated with MCC Melody](https://github.com/microchip-pic-avr-examples/avr64dd32-getting-started-with-rtc-mplabx-mcc), referred to as the **RTC Project**.
    - [Getting Started with Inter-Integrated Circuit (I2C) Using the AVR64DD32 Microcontroller with MCC Melody](https://github.com/microchip-pic-avr-examples/avr64dd32-getting-started-with-i2c-mplabx-mcc/), referred to as the **I2C Project**.
    - I also explored [this project](https://github.com/microchip-pic-avr-examples/avr64dd32-cnano-neopixels-mplab-mcc), but I couldn't get full functionality because it requires UI adaptation to work with the Curiosity Nano Explorer Board's digitally addressable LED ring (instead of a matrix). My focus for this research task was to quickly get two projects running.

#### RTC Project Findings
After executing the **Overflow_Interrupt_MCC.X** project, MPLABX successfully detected the target device (AVR64DD32) and calculated the memory ranges for programming.
        
        ```
        *****************************************************
        
         
        
        Currently loaded versions:
        Application version...........1.30.35 (0x01.0x1e.0x23)
        Tool pack version .............1.13.715
        Target voltage detected
        Target device AVR64DD32 found.
        Device Revision Id  = 0x13 (T)
        Device Id = 0x1e961a
        
        Calculating memory ranges for operation...
        
        Erasing...
        
        The following memory area(s) will be programmed:
        program memory: start address = 0x0, end address = 0x2ff
        configuration memory
        
        Programming complete
        ```
        
The program toggles the on-board LED each time the overflow interrupt occurs. This interrupt happens when the timer reaches its maximum value and resets to zero, indicating a specific period has passed. In this case, the overflow interrupt period is set to 500 ms. [Click here](https://share.icloud.com/photos/0d1oUqd1xjciht9O2DpI-VHZg) to view a video of the LED blinking on my board.

#### I2C Project Findings

After executing the I2C program, it compiled successfully, but the LEDs on the Curiosity Nano Explorer were not blinking. This likely requires addressing the components correctly in the code and setting the proper UART pin for output to the debugger or simulator. We did not cover the debugger in our last meeting with our sponsor, but this is not a concern in the getting started manual. We will be addressing real programs in the following sprints:
        
        ```
        *****************************************************
        
         
        
        Currently loaded versions:
        Application version...........1.25.116 (0x01.0x19.0x74)
        Tool pack version .............1.13.715
        Entering firmware upgrade mode
        
        Currently loaded versions:
        Boot version..................0.0.0 (0x00.0x00.0x00)
        Updating firmware application...
        
        Currently loaded versions:
        Application version...........1.30.35 (0x01.0x1e.0x23)
        Tool pack version .............1.13.715
        Target voltage detected
        Target device AVR64DD32 found.
        Device Revision Id  = 0x13 (T)
        Device Id = 0x1e961a
        
        Calculating memory ranges for operation...
        
        Erasing...
        
        The following memory area(s) will be programmed:
        program memory: start address = 0x0, end address = 0xbff
        configuration memory
        
        Programming complete
        ```

#### Lab 1 Meeting Recording Notes

UART

- Open MCC.
- In order for the UART Example to work correctly
    - Example Selection: UART Write String.
    - Example Implementation: Polled
- Those options were not showing last meeting because there's a UART and there's a USART peripheral and this is where things get a little confusing.
    - UART is a driver
    - USART0 is a peripheral driver
- We added a UART but it is a driver, so we needed to specify high level names. We needed to select a dependency called the UART PLIB, which is a thin layer between the UART driver and the bare metal.
    - We pick USART 0. Why? The reason is USART0 has access to ports 4 and 5.
    - Ports 4 and 5 are the UART pairs that talk to the onboard debugger on that Curiosity Nano board. So essentially, this is where the serial USB comes through, just like the serial in serial swap.
    - Those are the top level definitions.
        - Custom Name: UART
        - Requested Baudrate: 115200
        - Parity: None
        - Data Size: 8
        - Stop Bits: 1
        - Flow Control Mode: None
        - Dependency Selector: PLIB
    - Now options become available.

Timer0

- Set up a timer.
- Call it Timer0, enable it, and set it to interrupt driven.
- Under Dependency Selector choose TCB0
- I have an abstraction called timer 0. Which particular driver do I want? Well, I want to use TCB 0, which happens to be the same timer instance that the delay in the millis function in the Arduino core uses.
- Type B timers are very well suited for system ticks
- One millisecond is the same speed that the millis timer uses in Arduino. It tends to be fairly popular. Faster systems might use 500 microseconds, but the problem is, if you’re doing tasks, you’re down to some tight coding. For general brushless DC motor control, 1000 Hertz tends to be quick enough. Mechanical systems have resonant frequencies that are generally lower than a millisecond or kilohertz.
- **CLCKCTRL**: 4 MHz from bare metal to 24 MHz without worrying about power consumption.
- **Global Interrupts** Enabled
- **Configuration Bits**: Bits that are programmed in a special part of the flash that defines the personality of the part when it wakes up.  Bootloader and code space both set to 0.
- **Reset Pin Configuration**
    - Reset pin must be explicitly set (default is GPIO mode, which disables reset functionality).
- **Pin Configuration**
    - Pin 5 set as an output (referencing a bare-metal example).
    - MCC-generated files automatically handle file management.

Project: Blocking vs. Non Blocking

- **Clicking Generate** automatically creates mcc_generated files
    - Under examples/UART_Example you will find commented out code with examples for your main.c file in your project.
- Blocking and non blocking instances of both an LED blink and a UART
- system_initialize() makes calls to setup routines
    - Clock
    - Pin manager for P5
    - Timer B0
    - UART
    - Global and cleanups for CPU interrupts
- Timer0.TimeoutCallbackRegister(tcb_softtimer)
    - Every time the interrupt fires at 1 millisecond, Timer 0 triggers callback tcb_softtimer
    - tcb_softtimer handles timers using atomic operations

### What went well during the learning process?

- I was able to successfully execute programs from GitHub repositories by setting the correct configurations.

### Were there any topic(s) that were difficult to understand during the learning process?

- Understanding and analyzing `main.c` files is more challenging compared to Arduino sketches.
- I haven't yet figured out how to configure the correct addresses for components on the Curiosity Nano Explorer board.

### What troubles/issues did you encounter while working with the MPLABX system?

- The installation process for MPLABX was smooth but required a lot of disk space (23 GB).

### If you encountered any issues while working with MPLABX, were you able to fix them? If so, what steps did you take to fix the issues you encountered?

- No issues were encountered during the process.

### 