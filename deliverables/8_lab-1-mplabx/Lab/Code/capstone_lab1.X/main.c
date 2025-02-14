 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.2
 *
 * @version Package Version: 3.1.2
*/

/*
© [2025] Microchip Technology Inc. and its subsidiaries.

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

/*
    Main application
*/

char string_buffer[80];
volatile uint32_t timer = 0;

void UART_WriteString(const char *message);
uint32_t read_timer(void);
void clear_timer(void);
void tcb_softtimer(void);
void timer_reader(void);
void blink_led(void);

int main(void)
{
    SYSTEM_Initialize();

    Timer0.TimeoutCallbackRegister(tcb_softtimer);
    clear_timer();
    UART_WriteString("Program is starting...\r\n");
    
    _delay_ms(1000);
    
    while(1)
    {
        timer_reader();
    }    
}

void UART_WriteString(const char *message)
{
    for(int i = 0; i < (int)strlen(message); i++)
    {
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

void timer_reader(void)
{
    static unsigned int loop_count = 0;
    
    if (read_timer() > 10001u)
    {
        clear_timer();
        loop_count++;
        sprintf(string_buffer, "Loop count: %u\r\n", loop_count);
        UART_WriteString(string_buffer);
        blink_led();
    }
}

void blink_led(void) 
{
    clear_timer();
    PORTF.OUT &= ~(1 << 5);
    while (read_timer() < 200);
    PORTF.OUT |= (1 << 5);
}
