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
#include "scales.h"
#include <math.h>

void UART_WriteString(const char *message);

char uart_str[80];

int main(void) {
    SYSTEM_Initialize();
    pwm_init();
    vcnl_init();
    uint16_t proximity = 0;
    
    // Assign the ScaleBank to the variable 'bank', which contains different scales.
    ScaleBank bank = scale_bank;
    
    // Select the desired scale from the ScaleBank (in this case, the C Major scale).
    Scale chosen_scale = bank.c_major;
    
    // Get the length of the chosen scale (number of notes).
    int scale_length = chosen_scale.length;
    
    while (1) {
        // WARNING: Ensure you connect a jumper cable from pin PD1 to the AMP IN for the audio output to work correctly!

        // Read proximity value from the sensor.
        proximity = vncl_read_ps();
        
        // Logarithmically calculate the index based on proximity value.
        // This accounts for the nonlinear proximity sensor readings, mapping them to the scale length.
        // The equation was determined through a log regression process with Excel to best fit the data.
        float log_value = 0.9f * logf((float) proximity) - 1.5f;
        int index = (int) roundf(log_value);
        index = index < 0 ? 0 : (index >= scale_length ? scale_length - 1 : index);
        
        // Play the tone corresponding to the calculated index in the chosen scale.
        pwm_play_tone(chosen_scale.notes[index], 0.50f);
        
        // Print value to UART
        sprintf(uart_str, "Frequency: %f \r\n", chosen_scale.notes[index]);
        UART_WriteString(uart_str);
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