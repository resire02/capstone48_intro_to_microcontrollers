/*
 * Main Driver Program
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief Measures potentiometer readings on PD6 & PD7
 *
 * @version 1.0.0
 */

/*
? [2025] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
 */
#include "mcc_generated_files/system/system.h"
#include <string.h>
#include <stdio.h>

#define UART UART0

void UART_WriteString(const char *message);
char uart_str[80];
volatile uint32_t timer = 0UL;
void tcb_softtimer(void);
void clear_timer(void);
uint32_t read_timer(void);
void sample_voltages(void);


int main(void) 
{
    SYSTEM_Initialize();

    // set soft timer callback and clear_timer
    Timer0.TimeoutCallbackRegister(tcb_softtimer);
    clear_timer();
    
    UART_WriteString("MPLAB X IDE Lab 2 - ADC Reading\r\n");

    while (1) 
    {       
        sample_voltages();
    }
}

void sample_voltages(void)
{
    
    static unsigned adc_sample_count = 0;
    uint16_t chan7_cnt, chan6_cnt;
    
    // read ADC every 2 seconds
    if(read_timer() > 2000UL)
    {
        clear_timer();
        adc_sample_count++;
        
        // sample potentiometer on input on PD6/AIN6
        chan6_cnt = ADC0_ChannelSelectAndConvert(ADC_MUXPOS_AIN6_gc);
    
        // sample potentiometer on input on PD7/AIN7
        chan7_cnt = ADC0_ChannelSelectAndConvert(ADC_MUXPOS_AIN7_gc);      
    
        sprintf(uart_str,"sample: %d chan 6 %d chan 7 %d\r\n", adc_sample_count, chan6_cnt, chan7_cnt);
        UART_WriteString(uart_str);
    
    }
}

void UART_WriteString(const char *message)
{
    static uint16_t spinlock = 0;

    for (int i = 0; i < (int) strlen(message); i++) {
        while (!(UART.IsTxReady()))
            spinlock++;
        UART.Write(message[i]);
    }
}

void tcb_softtimer(void)
{
    cli();
    timer++;
    sei();
}

void clear_timer(void) 
{
    cli();
    timer = 0;
    sei();
}

uint32_t read_timer(void) 
{
    uint32_t timer_val;
    cli();
    timer_val = timer;
    sei();
    return timer_val;
}