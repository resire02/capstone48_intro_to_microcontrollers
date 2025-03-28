#include "mcc_generated_files/system/system.h"
#include <string.h>
#include <stdio.h>
#include <util/delay.h>
#include "systimer.h"

#define USR_LED 5           // on board LED PF5

void UART_WriteString(const char *message);
char uart_str[80];

void blink_led(void);
void blocking(void);
void non_blocking(void);
void sample_voltages(void);
uint8_t ADC_setsample(uint8_t sample_count);
void multi_sample_voltages(void);
void cycle_leds(void);

int16_t adc_val;

int main(void) 
{

    SYSTEM_Initialize();

    // set soft timer callback and clear_timers
    Timer0.TimeoutCallbackRegister(tcb_softtimer);
    clear_timer1();
    clear_timer2();
    clear_timer3();

    PORTF_set_pin_level(5, 1); // MCC pin control
    
    PORTC.DIR = (1 << 3); // bare metal GPIO control
    PORTC.OUTCLR = (1 << 3);

    
    UART_WriteString("MLAB X - MCC lab3 - ADC\r\n");
    sprintf(uart_str,"size of size_t %d\r\n",sizeof(size_t));
    UART_WriteString(uart_str);

    while (1) 
    {

    cycle_leds();

    }

}

/*
 * I2C GPIO Expander 1
 * MCP23008 IO Expander
*/
#define ADDR_IOEX1   0x25

void cycle_leds(void)
{   
    clear_timer1();
    while(read_timer1() < 100ul);

    uint8_t i2c_cmd[2] = { 0x00, 0x00 };
    size_t cmd_len = 2;

    TWI0_Write(ADDR_IOEX1,&i2c_cmd[0], cmd_len);
    while(TWI0_IsBusy());

    i2c_cmd[0] = 0x09;
    i2c_cmd[1] = 0xFE;
    bool incr = true;

    while(true)
    {
        TWI0_Write(ADDR_IOEX1,&i2c_cmd[0], cmd_len);
        while(TWI0_IsBusy());
        
        if (incr) i2c_cmd[1] = (i2c_cmd[1] << 1) | 0x01;
        else i2c_cmd[1] = (i2c_cmd[1] >> 1) | 0x80;
        if (i2c_cmd[1] == 0x7F || i2c_cmd[1] == 0xFE) incr = !incr;

        clear_timer1();
        while(read_timer1() < 50ul);
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

void blink_led(void) 
{
    clear_timer2();
    PORTF.OUT &= ~(1 << 5);
    while (read_timer2() < 200);
    PORTF.OUT |= (1 << 5);

}

