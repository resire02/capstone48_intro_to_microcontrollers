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
#include "pwm.h"
#include "pwm_notes.h"
#include <string.h>
#include <stdio.h>
#include "systimer.h"
#include "vcnl4200.h"

#define MAX_PROXIMITY 4095

void UART_WriteString(const char *message);

char uart_str[80];

float melody_notes[] = {
    NOTE_C4, NOTE_DS4, NOTE_F4, NOTE_G4, NOTE_AS4,
    NOTE_C5, NOTE_DS5, NOTE_F5, NOTE_G5, NOTE_AS5,
    NOTE_C6, NOTE_DS6, NOTE_F6, NOTE_G6, NOTE_AS6,
    NOTE_C7, NOTE_DS7, NOTE_F7, NOTE_G7, NOTE_AS7,
    NOTE_C8
};

size_t melody_length = (int16_t) (sizeof (melody_notes) / sizeof (float));

int main(void) {
    SYSTEM_Initialize();
    pwm_init();
    vcnl_init();
    uint16_t proximity = 0;
    uint16_t index = 0;

    while (1) {
        // You MUST connect a jumper cable from pin PD1 to AMP IN for this to work!
        proximity = vncl_read_ps();
        index = (unsigned int) (proximity * (melody_length - 1)) / MAX_PROXIMITY;
        sprintf(uart_str, "proximity: %d \r\n", proximity);
        UART_WriteString(uart_str);
        pwm_play_tone(melody_notes[index], 0.15f);
    }
}

void UART_WriteString(const char *message) {
    static uint16_t spinLock = 0;
    for (int i = 0; i < (int) strlen(message); i++) {
        while (!UART0.IsTxReady()) {
            spinLock++;
        };
        (void) UART0.Write(message[i]);
    }
}