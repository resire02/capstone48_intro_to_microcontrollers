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

void UART_WriteString(const char *message);
char uart_str[80];
volatile uint32_t timer = 0UL;
void tcb_softtimer(void);
void clear_timer(void);
uint32_t read_timer(void);
void multi_sample_voltages(void);

int main(void) 
{
    SYSTEM_Initialize();

    // set soft timer callback and clear_timer
    Timer0.TimeoutCallbackRegister(tcb_softtimer);
    clear_timer();
    
    UART_WriteString("MLAB X - MCC lab3 - ADC\r\n");

    while (1) 
    {       
        multi_sample_voltages();
    }
}


// translate sample numbers in ADC0 CTRLB byte values

uint8_t samplenum_index[2][8] = 
  {
      {0,1,2,3,4,5,6,7},
      {1,2,4,8,16,32,64,128}
  };



uint8_t ADC0_setsamplenum(uint8_t sample_count)
{

  uint8_t scan_index,ctrlb_val = 0xFF;
  uint8_t flag;
  
  for(scan_index = 0;scan_index < 8;scan_index++)
  {

    if(samplenum_index[1][scan_index] == sample_count)
      ctrlb_val = samplenum_index[0][scan_index];    // extract correct value CTRLB reg
  }

  if(ctrlb_val == 0xFF)
  {
      ctrlb_val = 0x00;      // set to single sample if no valid choice
      flag = false;
      
  }
    
  else flag = true;
  ADC0.CTRLB = ctrlb_val;
  return(flag);
}



#define SAMPLE_NUM 32


void multi_sample_voltages(void)
{
    // demonstrate  the ADC accumulation 
    
    static uint16_t adc_sample_count = 0;
    static uint32_t chan7_cnt,chan6_cnt;
    static uint16_t ch6_raw,ch7_raw;
    
    uint8_t flag;
    
    
    
    if(read_timer() > 1500lu)
    {
        
        clear_timer();
        adc_sample_count++;
        if(ADC0_setsamplenum(SAMPLE_NUM))
        {
            ADC0_ChannelSelect(ADC_MUXPOS_AIN6_gc);
            ADC0_ConversionStart();
            while(!ADC0_IsConversionDone());
            ch6_raw = ADC0.RES;
            ch6_raw /= (uint16_t)(SAMPLE_NUM);
            
            // correct for truncation
            if(SAMPLE_NUM == 32)
                ch6_raw *= 2;
            
            if(SAMPLE_NUM == 64)
                ch6_raw *= 4;
            
            if(SAMPLE_NUM == 128)
                ch6_raw *= 8;   
            
            ADC0_ChannelSelect(ADC_MUXPOS_AIN7_gc);
            ADC0_ConversionStart();
            while(!ADC0_IsConversionDone());
            ch7_raw = ADC0.RES;
            ch7_raw /= (uint16_t)(SAMPLE_NUM);
            
            // correct for truncation
            
            if(SAMPLE_NUM == 32)
                ch7_raw *= 2;
            
            if(SAMPLE_NUM == 64)
                ch7_raw *= 4;
            
            if(SAMPLE_NUM == 128)
                ch7_raw *= 8;
            
            sprintf(uart_str,"sample %04u accumulated samples %d\r\n",adc_sample_count,SAMPLE_NUM);
            UART_WriteString(uart_str);
            sprintf(uart_str,"chan 6 %04u chan 7 %04u \r\n",ch6_raw,ch7_raw);
            UART_WriteString(uart_str);
        }
                
        else 
        {
            
            sprintf(uart_str,"invalid number of samples specified");
            UART_WriteString(uart_str);
        }
       
           
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
    return (timer_val);
}