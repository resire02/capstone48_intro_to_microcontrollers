#include "mcc_generated_files/system/system.h"
#include <xc.h>

#define MCP_LEDS_ADDR 0x25
#define MCP_LEDS_IO_REG 0x09

void mcp_leds_init()
{
    // set all pins as outputs in IODIR register
    static uint8_t write_data[2] = { 0x00, 0x00 };
    while(TWI0_IsBusy());
    TWI0_Write(MCP_LEDS_ADDR, write_data, 2);
}

void mcp_write_leds(uint8_t val)
{
    static uint8_t write_data[2] = { MCP_LEDS_IO_REG, 0x00 };
    // invert input so that 1 represents ON and 0 represents OFF
    write_data[1] = ~val;
    while(TWI0_IsBusy());
    TWI0_Write(MCP_LEDS_ADDR, write_data, 2);
}