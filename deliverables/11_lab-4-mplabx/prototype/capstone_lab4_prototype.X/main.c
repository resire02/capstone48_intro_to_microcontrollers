#include "mcc_generated_files/system/system.h"
#include <string.h>
#include <stdio.h>
#include <util/delay.h>
#include "systimer.h"

#define UART UART0
#define USR_LED 5

#define VEML_I2C_ADDR 0x10
#define VEML_CLR_CMD_REG 0x04
#define VEML_RED_CMD_REG 0x05
#define VEML_GRN_CMD_REG 0x06
#define VEML_BLU_CMD_REG 0x07
#define VEML_IFR_CMD_REG 0X08
#define VEML_IDL_CMD_REG 0x0c

void UART_WriteString(const char *message);
void read_vncl_data(void);
void read_veml_data(void);

char uart_str[80];

int main(void)
{
    SYSTEM_Initialize();
    Timer0.TimeoutCallbackRegister(tcb_softtimer);
    UART_WriteString("Program is starting...\r\n");

    while (1) 
    {
        //read_veml_data();
        read_vncl_data();
    }

    return 0;
}

volatile uint16_t brightness = 0, 
                  red = 0, 
                  blue = 0, 
                  green = 0, 
                  infrared = 0;

void read_veml_data(void)
{
    UART_WriteString("Setting up VEML3328...\r\n");
    uint8_t write_payload[3] = { 0x00, 0x00, 0x00 };
    uint8_t read_payload[2] = { 0x00, 0x00 };
    
    // write default values into VEML3328
    while(TWI0_IsBusy());
    TWI0_Write(VEML_I2C_ADDR, write_payload, 3);
    
    // wait 100 MS for VEML3328 startup
    clear_timer1();
    while(read_timer1() < 100ul);
    
    while (1)
    {
        // read ID_L register, this only works if it's run in the loop by itself
        //write_payload[0] = VEML_IDL_CMD_REG;
        //while(TWI0_IsBusy());
        //TWI0_WriteRead(VEML_I2C_ADDR, write_payload, 1, read_payload, 2);
        //sprintf(uart_str, "This value should be 0x28 (40): %d\n\r", read_payload[0]);
        //UART_WriteString(uart_str);
        
        // read C_LSB and C_MSB registers
        write_payload[0] = VEML_CLR_CMD_REG;
        while(TWI0_IsBusy());
        TWI0_WriteRead(VEML_I2C_ADDR, write_payload, 1, read_payload, 2);
        brightness = (read_payload[1] << 8) | read_payload[0];
        
        // read R_LSB and R_MSB registers
        write_payload[0] = VEML_RED_CMD_REG;
        while(TWI0_IsBusy());
        TWI0_WriteRead(VEML_I2C_ADDR, write_payload, 1, read_payload, 2);
        red = (read_payload[1] << 8) | read_payload[0];
        
        // read G_LSB and G_MSB registers
        write_payload[0] = VEML_GRN_CMD_REG;
        while(TWI0_IsBusy());
        TWI0_WriteRead(VEML_I2C_ADDR, write_payload, 1, read_payload, 2);
        green = (read_payload[1] << 8) | read_payload[0];
        
        // read B_LSB and B_MSB registers
        write_payload[0] = VEML_BLU_CMD_REG;
        while(TWI0_IsBusy());
        TWI0_WriteRead(VEML_I2C_ADDR, write_payload, 1, read_payload, 2);
        blue = (read_payload[1] << 8) | read_payload[0];
        
        // read IR_LSB and IR_MSB
        write_payload[0] = VEML_IFR_CMD_REG;
        while(TWI0_IsBusy());
        TWI0_WriteRead(VEML_I2C_ADDR, write_payload, 1, read_payload, 2);
        infrared = (read_payload[1] << 8) | read_payload[0];
        
        sprintf(uart_str, "R: %u\t\tG: %u\t\tB: %u\t\tAMBIENT: %u\tIFR: %u\n\r", red, green, blue, brightness, infrared);
        UART_WriteString(uart_str);
        
        clear_timer1();
        while(read_timer1() < 1000ul);
    }
}

#define VNCL_I2C_ADDR 0x51
#define VNCL_ALS_CONF_REG 0x00
#define VNCL_PS_CONF1_CONF2_REG 0x03
#define VNCL_DATA_PS_REG 0x08
#define VNCL_DATA_ALS_REG 0x09
#define VNCL_DATA_WHITE_REG 0x0a
#define VNCL_DEVICE_INFO_REG 0x0e

volatile uint16_t proximity = 0, ambient = 0, white = 0;

void read_vncl_data(void)
{
    UART_WriteString("Setting up VNCL4200...\r\n");
    // 0x00 enables ALS_SD in ALS_CONF_L, 0x01 is default value for ALS_CONF_H
    uint8_t write_payload[3] = { VNCL_ALS_CONF_REG, 0x00, 0x01};
    uint8_t read_payload[2] = { 0x00, 0x00 };
    
    // initialize ALS_CONF register
    while(TWI0_IsBusy());
    TWI0_Write(VNCL_I2C_ADDR, write_payload, 3);
    
    // turn on proximity sensor through PS_CONF1
    write_payload[0] = VNCL_PS_CONF1_CONF2_REG;
    write_payload[1] = 0x00; // PS_CONF1
    write_payload[2] = 0x00; // PS_CONF2
    while(TWI0_IsBusy());
    TWI0_Write(VNCL_I2C_ADDR, write_payload, 3);
    
    while (1)
    {
        // grab MP Version from ID_L register, also doesn't work if not the only code in the loop
        //write_payload[0] = VNCL_DEVICE_INFO_REG;
        //while(TWI0_IsBusy());
        //TWI0_WriteRead(VNCL_I2C_ADDR, write_payload, 1, read_payload, 2);
        //sprintf(uart_str, "This value should be 88: %d\n\r", read_payload[0]);
        //UART_WriteString(uart_str);
        
        // read proximity data from 
        write_payload[0] = VNCL_DATA_PS_REG;
        TWI0_WriteRead(VNCL_I2C_ADDR, write_payload, 1, read_payload, 2);
        proximity = (read_payload[1] << 8) | read_payload[0];
        
        sprintf(uart_str, "PROX: %u\n\r", proximity);
        UART_WriteString(uart_str);
        
        clear_timer1();
        while(read_timer1() < 100ul);
    }
}

void UART_WriteString(const char *message)
{
    static uint16_t spinlock = 0;
    for(int i = 0; i < (int)strlen(message); i++)
    {
        while(!UART.IsTxReady())
        {
            spinlock++;
        };
        (void) UART.Write(message[i]);
    }
}