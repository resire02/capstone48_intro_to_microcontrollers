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
#include "pwm.h"
#include "pwm_notes.h"
#include <string.h>
#include <stdio.h>
#include "systimer.h"
#include "vcnl4200.h"
#include "scales.h"
#include <math.h>
#include "mcp23008.h"

void UART_WriteString(const char *message);
void read_sensor_and_play(int scale_index, float duty_cycle, float gate);
char uart_str[80];
float current_divisor = 1.0;

int main(void) {
    SYSTEM_Initialize();
    pwm_init();
    vcnl_init();  
    mcp23008_init();

    int current_scale_index = 0;
    uint32_t curr_gate = 0;

    // Simulated duty cycle
    float duty_cycle = 0.50f;

    while (1) {
        // WARNING: Ensure you connect a jumper cable from pin PD1 to the AMP IN for the audio output to work correctly!
        mcp23008_read_ioex2();
        
        // handle joystick inputs
        if (mcp23008_is_joystick_left())
        {
            current_scale_index = (current_scale_index - 1 + num_scales) % num_scales;
        }
        else if (mcp23008_is_joystick_right())
        {
            current_scale_index = (current_scale_index + 1) % num_scales;
        }
        else if (mcp23008_is_joystick_up())
        {
            if (current_divisor > 0.25) current_divisor /= 2.0;
        }
        else if (mcp23008_is_joystick_down())
        {
            if (current_divisor < 8.0) current_divisor *= 2.0;
        }
        else if (mcp23008_is_joystick_pressed())
        {
            switch (curr_gate)
            {
                case 0:
                    curr_gate = 50; break;
                case 50:
                    curr_gate = 100; break;
                case 100:
                    curr_gate = 250; break;
                case 250:
                    curr_gate = 500; break;
                case 500:
                    curr_gate = 0; break;
            }
            clear_timer2();
        }
        
        if (mcp23008_is_sw1_pressed())
        {
            duty_cycle = 0.50;
        }
        else if (mcp23008_is_sw2_pressed())
        {
            duty_cycle = 0.25;
        }
        else if (mcp23008_is_sw3_pressed())
        {
            duty_cycle = 0.05;
        }

        // Read sensor and set theremin to chosen scale and duty cycle
        read_sensor_and_play(current_scale_index, duty_cycle, curr_gate);
    }
}

void read_sensor_and_play(int scale_index, float duty_cycle, float gate) {
    static bool gate_on = false;
    
    // Initialize variable for proximity reading
    uint16_t proximity = 0;

    // Select the desired scale from the ScaleBank (in this case, the C Major scale).
    Scale chosen_scale = scale_bank[scale_index];

    // Get the length of the chosen scale (number of notes).
    int scale_length = chosen_scale.length;

    // Read proximity value from the sensor.
    proximity = vncl_read_ps();
    
    // Logarithmically calculate the index based on proximity value.
    // This accounts for the nonlinear proximity sensor readings, mapping them to the scale length.
    // The equation was determined through a log regression process with Excel to best fit the data.
    float log_value = 0.9f * logf((float) proximity) - 1.5f;
    int index = (int) roundf(log_value);
    index = index < 0 ? 0 : (index >= scale_length ? scale_length - 1 : index);

    // Update LEDs with current note
    mcp23008_write_leds(1 << (7 - index < 0 ? 0 : 7 - index));
    
    // Play the tone corresponding to the calculated index in the chosen scale.
    if (gate != 0)
    {
        if (gate_on) 
            pwm_play_tone(0, duty_cycle);
        else 
            pwm_play_tone(chosen_scale.notes[index] / current_divisor, duty_cycle);
        
        if (read_timer2() > gate)
        {
            gate_on = !gate_on;
            clear_timer2();
        }
    }
    else
    {
        pwm_play_tone(chosen_scale.notes[index] / current_divisor, duty_cycle);
    }
    
    // Print value to UART
//    sprintf(uart_str, "Frequency: %f \r\n", chosen_scale.notes[index]);
//    UART_WriteString(uart_str);
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