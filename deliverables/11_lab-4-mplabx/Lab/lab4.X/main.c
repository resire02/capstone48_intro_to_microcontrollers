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
#include "simpletimer.h"
#include "vcnl4200.h"
#include "mcp23008.h"
#include "veml3328.h"

#define UART UART0
#define PROXIMITY_THRESHOLD 100

void UART_WriteString(const char *message);

char uart_str[80];

int main(void)
{
    SYSTEM_Initialize();
    Timer0.TimeoutCallbackRegister(timer_callback);
    vcnl_init();
    mcp_leds_init();
    veml_init();

    UART_WriteString("MPLAB X Lab 4\n\r");
    clear_timer();
    while(read_timer() < 100);
    
    uint16_t proximity = 0;
    uint8_t led = 0, write_led = 0, i;
    uint16_t color[3] = { 0x00, 0x00, 0x00 };
    uint16_t light[2] = { 0x00, 0x00 };
    
    while(1)
    {
        // read proximity value
        proximity = vncl_read_ps();
        led = (uint8_t) (proximity / MCP_LED_CHUNK_SIZE);
        
        // enable expander IO LEDs based on proximity value
        write_led = proximity > PROXIMITY_THRESHOLD ? 0x80 : 0x00;
        for (i = 0; i < led; i++)
        {
            write_led >>= 1;
            write_led |= 0x80;
        }
        mcp_write_leds(write_led);
        
        // read color values every 100ms
        if (read_timer() > 100)
        {
            clear_timer();
            veml_read_colors(color);
            veml_read_brightness(light);
            sprintf(uart_str, "R: %u\tG: %u\tB: %u\tBRT: %u\tIFR: %u\n\r", color[0], color[1], color[2], light[0], light[1]);
            UART_WriteString(uart_str);
        }
    }
}

void UART_WriteString(const char *message)
{
    static uint16_t spinLock = 0;
    for(int i = 0; i < (int)strlen(message); i++)
    {
        while(!UART.IsTxReady())
        {
            spinLock++;
        };
        (void) UART.Write(message[i]);
    }
}