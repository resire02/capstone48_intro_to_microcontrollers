/*
 * File:   mcp23008.c
 * Author: 
 *
 * Created on April 27, 2025, 3:11 PM
 */
#include "mcc_generated_files/system/system.h"
#include <xc.h>
#include "mcp23008.h"

#define ADDR_IOEX1 0x25
#define ADDR_IOEX2 0x24
#define MCP23008_REG_IODIR 0x00
#define MCP23008_REG_GPPU 0x06
#define MCP23008_REG_PORT 0x09

#define JOYSTICK_UP (1 << 0)
#define JOYSTICK_DOWN (1 << 2)
#define JOYSTICK_LEFT (1 << 1)
#define JOYSTICK_RIGHT (1 << 3)
#define JOYSTICK_PRESSED (1 << 4)

static uint8_t write_data[2] = {0, 0};
static volatile uint8_t joystick_read = 0;

/* initializes the MCP23008 IO Expander LEDs */
void mcp23008_init(void)
{
    /* Joystick initialization */
    write_data[0] = MCP23008_REG_IODIR; /* select direction register */
    write_data[1] = 0xFF; /* set joystick pins as input */
    while (TWI0_IsBusy());
    TWI0_Write(ADDR_IOEX2, write_data, 2);
    write_data[0] = MCP23008_REG_GPPU; /* select pull-up register */
    write_data[1] = 0xFF; /* enable pull-ups for joystick pins */
    while (TWI0_IsBusy());
    TWI0_Write(ADDR_IOEX2, write_data, 2);
    
    /* LED initialization */
    write_data[0] = MCP23008_REG_IODIR; /* select direction register */
    write_data[1] = 0x00; /* set all LEDs as output */
    while (TWI0_IsBusy());
    TWI0_Write(ADDR_IOEX1, write_data, 2);
    write_data[0] = MCP23008_REG_PORT; /* set default register to port */
    mcp23008_write_leds(0x00); /* clear off LEDs */
}

/* sets the leds on/off */
void mcp23008_write_leds(uint8_t state)
{
    write_data[1] = ~state;
    while (TWI0_IsBusy());
    TWI0_Write(ADDR_IOEX1, write_data, 2);
}

void mcp23008_read_joystick(void)
{
    uint8_t joystick_cmd = MCP23008_REG_PORT;
    uint8_t read_in;
    
    /* request to read */
    while (TWI0_IsBusy());
    TWI0_Write(ADDR_IOEX2, &joystick_cmd, 1);
    
    /* read joystick data */
    while (TWI0_IsBusy());
    TWI0_Read(ADDR_IOEX2, &read_in, 1);
    
    if (joystick_read != read_in) joystick_read = read_in;
}

int mcp23008_is_joystick_up(void)
{
    if(!(joystick_read & JOYSTICK_UP))
        return 1;
    else
        return 0;
}

int mcp23008_is_joystick_down(void)
{
    if(!(joystick_read & JOYSTICK_DOWN))
        return 1;
    else
        return 0;
}

int mcp23008_is_joystick_left(void)
{
    if(!(joystick_read & JOYSTICK_LEFT))
        return 1;
    else
        return 0;
}

int mcp23008_is_joystick_right(void)
{
    if(!(joystick_read & JOYSTICK_RIGHT))
        return 1;
    else
        return 0;
}

int mcp23008_is_joystick_pressed(void)
{
    if(!(joystick_read & JOYSTICK_PRESSED))
        return 1;
    else
        return 0;
}