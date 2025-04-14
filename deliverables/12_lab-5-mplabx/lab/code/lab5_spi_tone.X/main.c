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
#include "systimer.h"           // system timers
#include "sine_wave.h"          // sine wave data

void UART_WriteString(const char *message);
char uart_str[80];


// MCP4821 12 bit DAC / SPI interface
// chip select IO26 Explorer

#define DAC_CS  (1 << 2)

// AVR64DD32 C-Nano board LED on PORTF bit 5

#define CNANO_LED (1 << 5)

void dac_init(void);
void play_tone(void);


inline void board_led_on(void) { do PORTF.OUTCLR = CNANO_LED; while(0);}
inline void board_led_off(void) { do PORTF.OUTSET = CNANO_LED; while(0);}

int main(void) 
{

    SYSTEM_Initialize();

    systimer_init();
    
    PORTF.DIRSET = CNANO_LED;

    UART_WriteString("MLAB X - MCC lab5 - SPI + DAC \r\n");
    
    dac_init();
    
    while (1) 
    {
       play_tone();
       clear_timer1();
       while(read_timer1() < 2000UL);
    }
    
}

/*
 
 I2C GPIO Expander 1
 MCP23008 IO Expander
  
*/

void dac_init()
{
    // configure the chip select
    
    PORTC.DIRSET = DAC_CS;
    PORTC.OUTSET = DAC_CS;
    SPI0_Open(HOST_CONFIG);
}


void play_tone(void)
{    
    
    static volatile int array_index, sample;  
    static volatile uint8_t high_byte,low_byte;
    
    clear_timer1();
    board_led_on();
    
    while(read_timer1() < 100UL) // play a two second tone
    {
        for(array_index = 0;array_index < 199;array_index += 1)       // array step 4 gets about 1.3 kHz saw tooth
          {

            sample = sine_wave[array_index] + 2048;       // add DC offset
            high_byte = (uint8_t)(sample >> 8);
            high_byte |= 0x30;                            // set gain X1 bit
            low_byte = (uint8_t)(sample & 0xFF);
            
            PORTC.OUTCLR = DAC_CS;
            
            SPI0_ByteExchange(high_byte);
            SPI0_ByteExchange(low_byte);
            
            PORTC.OUTSET = DAC_CS;
            
        }
        
    }
    
    board_led_off();
    
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