# Self Learning Evaluation

### Capstone Member: Gonzalo Allendes

### Sprint Name: MPLABX Timer0, UART, I2C, and ADC.

### Link to Taiga Task: [Task 214](https://tree.taiga.io/project/bookstrong-introduction-to-microcontroller/task/214)

### Sprint Topic: Blocking and Non-Blocking Instances of an LED and UART.

---

### Document your research in this section

#### Exploration of Sponsor Content for Lab 1:

The code in Lab 1 is an MPLAB X Project that controls an onboard LED and communicates
via UART. It initalizes system configurations, sets up timers, and demonstrates
both blocking and non-blocking execution methods with the **millis function** and the
**TCB** respectively.

I am breaking down the code.

1. Includes and definitions.

        #include "mcc_generated_files/system/system.h"
        #include <string.h>
        #include <stdio.h>
        #include <util/delay.h>
        #define USR_LED 5  // on board LED PF5


2. Global variables. - This is actually a longer list.
        
        char uart_str[80]; 
        volatile uint32_t timer1, timer2, timer3 = 0UL;

3. Initialization (Inside main)

         SYSTEM_Initialize(); // sets up settings
         Timer0.TimeoutCallbackRegister(tcb_softtimer); // Registers tcb_softtimer() as callback function for Timer0. This means tcb_softtimer() will run automatically at every timer tick, which is set to 1 ms.

4. Setup functions inside main.

         clear_timer1(); // resets timer values
         clear_timer2();
         PORTF_set_pin_level(5, 1); // turns on PF5 (board is active low, LED initially off)
         PORTC.DIR = (1 << 3); // Sets PC3 as output
         PORTC.OUTCLR = (1 << 3); // Clears PC3 
         _delay_ms(500); // blocking delay

5. Main loop

         while (1) {
            blocking();
            // non_blocking();
         }

6. Blocking vs. Non-Blocking functions

         The main difference between both is the use of _delay_ms(1000) in the blocking function and the use of
         timer1 to check if 1 second has passed in the non_blocking function. The second approach allows the program to continue.

7. READ THIS

         Why do we need Timer0?!?!
         Timer0 is configured to generate an interrupt at a set interval (tick rate), set at 1 ms in this project.
         Timer0 is passed interrupt handler function tcb_softtimer(), which simply increments the three timers at that moment.
         Of course it disables interrupts before doing what it needs to do and then enables them back again.
               --- That is the point of cli() and sei()
         Clear and read timer functions just clear and reset the timer at a time interval defined by the user in the bigger function.
         There you go. Simple!!
