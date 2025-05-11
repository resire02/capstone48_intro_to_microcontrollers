/*
 * Main Driver Program
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief Demonstrates blocking & nonblocking methods in code
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
#include <util/delay.h>

char uart_string[80];
volatile uint32_t timer = 0;

void UART_WriteString(const char *message);
uint32_t read_timer(void);
void clear_timer(void);
void tcb_softtimer(void);
void non_blocking(void);
void blocking(void);
void blink_led(void);

int main(void)
{
    SYSTEM_Initialize();
    PORTF_set_pin_level(5, 1);
    UART_WriteString("Program is starting...\r\n");
    
    _delay_ms(1000);
    
    Timer0.TimeoutCallbackRegister(tcb_softtimer);
    clear_timer();
    
    while(1)
    {
        non_blocking();
        //blocking();
    }    
}

void UART_WriteString(const char *message)
{
    static uint16_t spinlock = 0;
    for(int i = 0; i < (int)strlen(message); i++)
    {
        while(!UART0.IsTxReady())
            spinlock++;
        (void) UART0.Write(message[i]);
    }
}

uint32_t read_timer(void)
{
    uint32_t timer_val;
    cli();
    timer_val = timer;
    sei();
    return timer_val;
}

void clear_timer(void)
{
    cli();
    timer = 0;
    sei();
}

void tcb_softtimer(void)
{
    cli();
    timer++;
    sei();
}

void non_blocking(void)
{
    static unsigned int loop_count = 0;
    
    if (read_timer() > 1001)
    {
        loop_count++;
        sprintf(uart_string, "Loop count: %u\r\n", loop_count);
        UART_WriteString(uart_string);
        blink_led();
    }
}

void blocking(void)
{
    static unsigned int loop_count = 0;
    loop_count++;
    sprintf(uart_string, "Loop count: %u\r\n", loop_count);
    UART_WriteString(uart_string);
    blink_led();
    _delay_ms(1000);
}

void blink_led(void)
{
    clear_timer();
    PORTF.OUT &= ~(1 << 5);
    while (read_timer() < 1000);
    PORTF.OUT |= (1 << 5);
    clear_timer();
}