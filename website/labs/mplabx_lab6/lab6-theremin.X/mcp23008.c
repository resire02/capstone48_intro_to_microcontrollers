/*
 * File:   mcp23008.c
 * Author: Felix Leong
 *
 * Created on April 27, 2025, 3:11 PM
 */
#include "mcc_generated_files/system/system.h"
#include <xc.h>
#include "mcp23008.h"
#include "systimer.h"

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
#define SW1_PRESSED (1 << 7)
#define SW2_PRESSED (1 << 6)
#define SW3_PRESSED (1 << 5)

static uint8_t write_data[2] = {0, 0};
static volatile uint8_t ioex2_read = 0;
static uint8_t ioex2_state = 0;

//volatile unsigned char joystick_debug = 0;

/* initializes the MCP23008 IO Expander LEDs */
void mcp23008_init(void)
{
    /* Joystick initialization */
    write_data[0] = MCP23008_REG_IODIR; /* select direction register */
    write_data[1] = 0xFF; /* set joystick pins as input */
    TWI0_Write(ADDR_IOEX2, write_data, 2);
    while (TWI0_IsBusy());
    write_data[0] = MCP23008_REG_GPPU; /* select pull-up register */
    write_data[1] = 0xFF; /* enable pull-ups for joystick pins */
    TWI0_Write(ADDR_IOEX2, write_data, 2);
    while (TWI0_IsBusy());
    
    /* LED initialization */
    write_data[0] = MCP23008_REG_IODIR; /* select direction register */
    write_data[1] = 0x00; /* set all LEDs as output */
    TWI0_Write(ADDR_IOEX1, write_data, 2);
    while (TWI0_IsBusy());            
    mcp23008_write_leds(0);
    
    /* Timer initialization for timeout */
    timer_init();
}

/* sets the LEDs on/off */
void mcp23008_write_leds(uint8_t state)
{
    write_data[0] = MCP23008_REG_PORT;
    write_data[1] = ~state;
    TWI0_Write(ADDR_IOEX1, &write_data[0], 2);
    while(TWI0_IsBusy());
}

void mcp23008_read_ioex2(void)
{
    static uint8_t joystick_cmd = MCP23008_REG_PORT;
    uint8_t read_in;
    
    /* request to read */
    TWI0_Write(ADDR_IOEX2, &joystick_cmd, 1);
    while (TWI0_IsBusy());
    
    /* read joystick data */
    TWI0_Read(ADDR_IOEX2, &read_in, 1);
    while (TWI0_IsBusy());

    //joystick_debug = read_in;
    
    /* update state if different */
    if (ioex2_read != read_in)
    {
        ioex2_state &= ~read_in; /* reset flag for pins without input */
        ioex2_read = read_in;
    }
}

/* returns 1 if joystick is up, returns 0 if joystick is not up or timeout period has not expired */
bool mcp23008_is_joystick_up(void)
{
    if (!(ioex2_read & JOYSTICK_UP)) /* on input detected */
    {
        if (!(ioex2_state & JOYSTICK_UP)) /* never triggered since unpress */
        {
            ioex2_state |= JOYSTICK_UP; /* set input flag to prevent retrig */
        }
        else if (read_timer1() < IOEX2_TIMEOUT)
        {
            return false;
        }
        
        clear_timer1(); /* reset timeout counter */
        return true;
    }
    
    return false;
}

/* returns 1 if joystick is down, returns 0 if joystick is not down or timeout period has not expired */
bool mcp23008_is_joystick_down(void)
{
    if (!(ioex2_read & JOYSTICK_DOWN)) /* on input detected */
    {
        if (!(ioex2_state & JOYSTICK_DOWN)) /* never triggered since unpress */
        {
            ioex2_state |= JOYSTICK_DOWN; /* set input flag to prevent retrig */
        }
        else if (read_timer1() < IOEX2_TIMEOUT)
        {
            return false;
        }
        
        clear_timer1(); /* reset timeout counter */
        return true;
    }
    
    return false;
}

/* returns 1 if joystick is left, returns 0 if joystick is not left or timeout period has not expired */
bool mcp23008_is_joystick_left(void)
{
    if (!(ioex2_read & JOYSTICK_LEFT)) /* on input detected */
    {
        if (!(ioex2_state & JOYSTICK_LEFT)) /* never triggered since unpress */
        {
            ioex2_state |= JOYSTICK_LEFT; /* set input flag to prevent retrig */
        }
        else if (read_timer1() < IOEX2_TIMEOUT)
        {
            return false;
        }
        
        clear_timer1(); /* reset timeout counter */
        return true;
    }
    
    return false;
}

/* returns 1 if joystick is right, returns 0 if joystick is not right or timeout period has not expired */
bool mcp23008_is_joystick_right(void)
{
    if (!(ioex2_read & JOYSTICK_RIGHT)) /* on input detected */
    {
        if (!(ioex2_state & JOYSTICK_RIGHT)) /* never triggered since unpress */
        {
            ioex2_state |= JOYSTICK_RIGHT; /* set input flag to prevent retrig */
        }
        else if (read_timer1() < IOEX2_TIMEOUT)
        {
            return false;
        }
        
        clear_timer1(); /* reset timeout counter */
        return true;
    }
    
    return false;
}

/* returns 1 if joystick is right, returns 0 if joystick is not right or timeout period has not expired */
bool mcp23008_is_sw1_pressed(void)
{
    if (!(ioex2_read & SW1_PRESSED)) /* on input detected */
    {
        if (!(ioex2_state & SW1_PRESSED)) /* never triggered since unpress */
        {
            ioex2_state |= SW1_PRESSED; /* set input flag to prevent retrig */
        }
        else if (read_timer1() < IOEX2_TIMEOUT)
        {
            return false;
        }
        
        clear_timer1(); /* reset timeout counter */
        return true;
    }
    
    return false;
}

/* returns 1 if joystick is right, returns 0 if joystick is not right or timeout period has not expired */
bool mcp23008_is_sw2_pressed(void)
{
    if (!(ioex2_read & SW2_PRESSED)) /* on input detected */
    {
        if (!(ioex2_state & SW2_PRESSED)) /* never triggered since unpress */
        {
            ioex2_state |= SW2_PRESSED; /* set input flag to prevent retrig */
        }
        else if (read_timer1() < IOEX2_TIMEOUT)
        {
            return false;
        }
        
        clear_timer1(); /* reset timeout counter */
        return true;
    }
    
    return false;
}

bool mcp23008_is_sw3_pressed(void)
{
    if (!(ioex2_read & SW3_PRESSED)) /* on input detected */
    {
        if (!(ioex2_state & SW3_PRESSED)) /* never triggered since unpress */
        {
            ioex2_state |= SW3_PRESSED; /* set input flag to prevent retrig */
        }
        else if (read_timer1() < IOEX2_TIMEOUT)
        {
            return false;
        }
        
        clear_timer1(); /* reset timeout counter */
        return true;
    }
    
    return false;
}

/* returns 1 if joystick is pressed, returns 0 if joystick is not pressesd or timeout period has not expired */
bool mcp23008_is_joystick_pressed(void)
{
    if (!(ioex2_read & JOYSTICK_PRESSED)) /* on input detected */
    {
        if (!(ioex2_state & JOYSTICK_PRESSED)) /* never triggered since unpress */
        {
            ioex2_state |= JOYSTICK_PRESSED; /* set input flag to prevent retrig */
        }
        else if (read_timer1() < IOEX2_TIMEOUT)
        {
            return false;
        }
        
        clear_timer1(); /* reset timeout counter */
        return true;
    }
    
    return false;
}