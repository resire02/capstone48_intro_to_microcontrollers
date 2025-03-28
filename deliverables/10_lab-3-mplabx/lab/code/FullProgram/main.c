#include "mcc_generated_files/system/system.h"
#include <string.h>
#include <stdio.h>
#include "systimer.h"

#define ADDR_IOEX1   0x25
#define ADDR_IOEX2   0x24

void UART_WriteString(const char *message);
char uart_str[80];
void cycle_leds(void);
void read_switches(void);

int main(void) 
{
    SYSTEM_Initialize();
    Timer0.TimeoutCallbackRegister(tcb_softtimer);
    UART_WriteString("MLAB X - MCC lab3 - ADC\r\n");
    while (1) 
    {
          cycle_leds();
          // read_switches();
    }
}

void cycle_leds(void) {
    
    uint8_t i2c_cmd[2] = { 0x00, 0x00 };
    size_t cmd_len = 2;
    TWI0_Write(ADDR_IOEX1, &i2c_cmd[0], cmd_len);
    while(TWI0_IsBusy());
    
    i2c_cmd[0] = 0x09;
    i2c_cmd[1] = 0xFE; // 8-bit binary: 0b11111110.

    bool incr = true;
    
    clear_timer1();
    while(read_timer1() < 500);
    
    while(true)
    {   
        TWI0_Write(ADDR_IOEX1,&i2c_cmd[0], cmd_len);
        while(TWI0_IsBusy());
        if (incr) i2c_cmd[1] = (i2c_cmd[1] << 1) | 0x01;            //(1)
        else i2c_cmd[1] = (i2c_cmd[1] >> 1) | 0x80;                 //(2)
        if (i2c_cmd[1] == 0x7F || i2c_cmd[1] == 0xFE) incr = !incr;
        clear_timer1();
        while(read_timer1() < 500);
    }
}

void read_switches(void) {
    uint8_t i2c_cmd[2] = {0x00, 0xFF};
    size_t cmd_len = 2;

    TWI0_Write(ADDR_IOEX2,&i2c_cmd[0], cmd_len);
    while(TWI0_IsBusy());

    i2c_cmd[0] = 0x06;          // GPPU
    i2c_cmd[1] = 0xFF;

    TWI0_Write(ADDR_IOEX2, &i2c_cmd[0], cmd_len);
    while(TWI0_IsBusy());

    while (true) {
        static uint8_t last_state = 0xFF;
        uint8_t switch_state;
        uint8_t i2c_cmd = 0x09;          // GPIO
        
        TWI0_Write(ADDR_IOEX2, &i2c_cmd, 1);
        while (TWI0_IsBusy());
        
        TWI0_Read(ADDR_IOEX2, &switch_state, 1);
        while (TWI0_IsBusy());
        
        if (switch_state != last_state && switch_state != 0xFF) {
            last_state = switch_state;
            
            switch (switch_state) {
                case 0b01111111: // Left switch pressed
                    sprintf(uart_str,"Left switch pressed\r\n");
                    break;
                case 0b10111111: // Middle switch pressed
                    sprintf(uart_str,"Middle switch pressed\r\n");
                    break;
                case 0b11011111: // Right switch pressed
                    sprintf(uart_str,"Right switch pressed\r\n");
                    break;
                case 0b00111111: // Left & Middle pressed
                    sprintf(uart_str, "Left and Middle switches pressed\r\n");
                    break;
                case 0b01011111: // Left & Right pressed
                    sprintf(uart_str, "Left & Right switches pressed\r\n");
                    break;
                case 0b10011111: // Middle & Right pressed
                    sprintf(uart_str, "Middle & Right switches pressed\r\n");
                    break;
                case 0b00011111: // All three switches pressed
                    sprintf(uart_str, "All switches pressed\r\n");
                    break;
            }
            UART_WriteString(uart_str);
        }   
    }
}

void UART_WriteString(const char *message)
{
    for (int i = 0; i < (int) strlen(message); i++) {
        while (!(UART.IsTxReady()))
        {
        };
        (void)UART.Write(message[i]);
    }
}