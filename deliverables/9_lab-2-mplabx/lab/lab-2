## Required Materials

* MP LAB X IDE and Compiler
* Curiosity Nano AVR64DD32 board
* USB to connect board to computer

## Learning Objective

* Using MCC Melody
* Viewing pin configurations
* Configuring and using the ADC

## Code overview
For this code will will use the following header files.

    #include "mcc_generated_files/system/system.h"
    #include <string.h>
    #include <stdio.h>
    #include <util/delay.h>

We will define the USR_LED as follows:

    #define USR_LED 5  // On-board LED PF5


We will also create two global variables: the first is the buffer for formatting the UART messages, and the second will be the software timers used for non-blocking delays:
    char uart_str[80];
    volatile uint32_t timer1, timer2, timer3 = 0UL;

The following functions handle timing, LED blinking, ADC sampling, UART transmission, and system tasks:
    void UART_WriteString(const char *message);
    void tcb_softtimer(void);
    void clear_timer1(void);
    void clear_timer2(void);
    void clear_timer3(void);
    uint32_t read_timer1(void);
    uint32_t read_timer2(void);
    uint32_t read_timer3(void);
    void blink_led(void);
    void blocking(void);
    void non_blocking(void);
    void loop_task(void);
    void sample_voltages(void);

Global Variables

    int16_t adc_val;

Main Function Overview
In the main loop, we initialize and set up the microcontroller. We also register a software timer callback to update the three timers. The main loop configures the LED and the general-purpose output pin, and then sends a startup message over UART. Once everything is set up, the main function continuously calls the sample_voltages() function.
    int main(void) 
    {
        SYSTEM_Initialize();
    
        // Set software timer callback and clear timers
        Timer0.TimeoutCallbackRegister(tcb_softtimer);
        clear_timer1();
        clear_timer2();
        clear_timer3();
    
        PORTF_set_pin_level(5, 1); // MCC pin control
        PORTC.DIR = (1 << 3); // Bare metal GPIO control
        PORTC.OUTCLR = (1 << 3);
    
        UART_WriteString("MLAB X - MCC lab3 - ADC\r\n");
    
        while (1) 
        {
            // loop_task();            
            sample_voltages();
        }
    }

Loop Task Function
The loop_task() function uses Timer1 and sends a UART message with the loop count. It also calls the blink_led() function to toggle the LED.

    void loop_task(void) 
    {
        static unsigned int loop_count = 0;
    
        if (read_timer1() > 1000LU) 
        {
            clear_timer1();
            loop_count++;
            sprintf(uart_str, "loop count %u\r\n", loop_count);
            UART_WriteString(uart_str);
            blink_led();
        }
    }
Sample Voltages Function
The sample_voltages() function uses Timer3 for periodic ADC sampling. It reads the values from ADC channel 6 and channel 7, then formats the data and sends the results via UART.
    void sample_voltages(void)
    {
        static unsigned adc_sample_count = 0;
        uint16_t chan7_cnt, chan6_cnt;
        
        if (read_timer3() > 2000LU)
        {
            clear_timer3();
            adc_sample_count++;
            
            // Sample potentiometer on input PF4/AIN6
            chan6_cnt = ADC0_ChannelSelectAndConvert(ADC_MUXPOS_AIN6_gc);      // Channel definition from ioavr64dd32.h
        
            // Sample potentiometer on input PF5/AIN7
            chan7_cnt = ADC0_ChannelSelectAndConvert(ADC_MUXPOS_AIN7_gc);
        
            sprintf(uart_str, "sample: %d chan 6 %d chan 7 %d\r\n", adc_sample_count, chan6_cnt, chan7_cnt);
            UART_WriteString(uart_str);
        }
    }


Blocking Function
This function increments the loop count, sends a message, then delays for 1 second.

    void blocking(void) 
    {
        static unsigned int loop_count = 0;
    
        loop_count++;
        sprintf(uart_str, "loop count %u\r\n", loop_count);
        UART_WriteString(uart_str);
    
        _delay_ms(1000);
    }

UART Write Function
This function waits for UART to be ready before sending each character. It also uses a spinlock counter for debugging.
    void UART_WriteString(const char *message)
    {
        static uint16_t spinlock = 0;
    
        for (int i = 0; i < (int)strlen(message); i++) {
            while (!(UART.IsTxReady()))
                spinlock++;
            UART.Write(message[i]);
        }
    }
LED Blinking Function
This function toggles the LED by waiting for 200 ms, then turning it off.
    void blink_led(void) 
    {
        clear_timer2();
        PORTF.OUT &= ~(1 << 5);
        while (read_timer2() < 200);
        PORTF.OUT |= (1 << 5);
    }

Software Timer Callback Function
This function is called by Timer0 and increments timer1, timer2, and timer3. The cli() and sei() functions are used to prevent other timer interrupts from causing issues.

    void tcb_softtimer(void)
    {
        cli();
        timer1++;
        timer2++;
        timer3++;
        sei();
    }
Timer Access Functions
These functions provide safe access to timer1, timer2, and timer3 using interrupt locking to ensure atomic read and write operations.

    void clear_timer1(void)
    {
        cli();
        timer1 = 0;
        sei();
    }
    
    void clear_timer2(void) 
    {
        cli();
        timer2 = 0;
        sei();
    }
    
    uint32_t read_timer1(void)
    {
        uint32_t timer1_val;
        cli();
        timer1_val = timer1;
        sei();
        return (timer1_val);
    }
    
    uint32_t read_timer2(void) 
    {
        uint32_t timer2_val;
        cli();
        timer2_val = timer2;
        sei();
        return (timer2_val);
    }
    
    void clear_timer3(void) 
    {
        cli();
        timer3 = 0;
        sei();
    }
    
    uint32_t read_timer3(void) 
    {
        uint32_t timer3_val;
        cli();
        timer3_val = timer3;
        sei();
        return (timer3_val);
    }
3.1 Differential ADC Measurement
To measure the differential voltage between channels 6 and 7, we'll make the following changes to the sample_voltages() function:

At the top of the function, add a variable to store the differential ADC measurement:
    int16_t chan76_cnt:

Next, add the following code before the UART transmission:
    // Enable differential mode
    ADC0.CTRLA |= ADC_CONVMODE_DIFF_gc;
    ADC0.MUXPOS = ADC_MUXPOS_AIN7_gc;
    ADC0.MUXNEG = ADC_MUXPOS_AIN6_gc;
    
    ADC0.COMMAND |= ADC_STCONV_bm;
    
    while (!(ADC0.INTFLAGS & 0x01));
    chan76_cnt = ADC0.RES;
    
    // Disable differential mode
    ADC0.CTRLA &= ~(ADC_CONVMODE_DIFF_gc);
This sets up the ADC to measure the voltage difference between channels 6 and 7 and will display the result.
3.2 Multi-Sampling
For section 3.2, we will modify the code to sample multiple times and average the values.

Remove the following lines as they are no longer needed:
    uint8_t ADC_setsample(uint8_t sample_count);
    void multi_sample_voltages(void);
Replace sample_voltages(); with multi_sample_voltages();.

Implement the new multi_sample_voltages() function:
    int8_t samplenum_index[2][8] = 
    {
        {0, 1, 2, 3, 4, 5, 6, 7},
        {1, 2, 4, 8, 16, 32, 64, 128}
    };
    
    uint8_t ADC0_setsamplenum(uint8_t sample_count)
    {
        uint8_t scan_index, ctrlb_val = 0xFF;
        uint8_t flag;
      
        for (scan_index = 0; scan_index < 8; scan_index++)
        {
            if (samplenum_index[1][scan_index] == sample_count)
                ctrlb_val = samplenum_index[0][scan_index];    // Extract correct value for CTRLB register
        }
    
        if (ctrlb_val == 0xFF)
        {
            ctrlb_val = 0x00;  // Set to single sample if no valid choice
            flag = false;
        }
        else
            flag = true;
    
        ADC0.CTRLB = ctrlb_val;
        return flag;
    }
    
    #define SAMPLE_NUM 128
    
    void multi_sample_voltages(void)
    {
        static uint16_t adc_sample_count = 0;
        static uint32_t chan7_cnt, chan6_cnt;
        static uint16_t ch6_raw, ch7_raw;
        
        uint8_t flag;
    
        if (read_timer3() > 1500LU)
        {
            clear_timer3();
            adc_sample_count++;
            
            if (ADC0_setsamplenum(SAMPLE_NUM))
            {
                ADC0_ChannelSelect(ADC_MUXPOS_AIN6_gc);
                ADC0_ConversionStart();
                while (!ADC0_IsConversionDone());
                ch6_raw = ADC0.RES;
                ch6_raw /= (uint16_t)SAMPLE_NUM;
    
                ADC0_ChannelSelect(ADC_MUXPOS_AIN7_gc);
                ADC0_ConversionStart();
                while (!ADC0_IsConversionDone());
                ch7_raw = ADC0.RES;
                ch7_raw /= (uint16_t)SAMPLE_NUM;
    
                sprintf(uart_str, "sample: %04u chan 6 %04u chan 7 %04u\r\n", adc_sample_count, ch6_raw, ch7_raw);
            }
            else
            {
                sprintf(uart_str, "Invalid number of samples specified");
            }
    
            UART_WriteString(uart_str);
        }
    }
This function performs multiple ADC measurements, averages the results, and displays them. The SAMPLE_NUM macro defines how many samples to take.
