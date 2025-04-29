/* 
 * File:   mcp23008.h
 * Author: Felix Leong
 *
 * Created on April 27, 2025, 3:07 PM
 */

#ifndef MCP23008_H
#define	MCP23008_H

#ifdef	__cplusplus
extern "C" {
#endif
   
#define IOEX2_TIMEOUT 250UL
    
/* initializes the MCP23008 IO Expander LEDs */
void mcp23008_init(void);

/* sets the leds on/off */
void mcp23008_write_leds(unsigned char state);

/* reads joystick values */
void mcp23008_read_ioex2(void);

/* returns 1 if joystick is up, returns 0 if joystick is not up or timeout period has not expired */
bool mcp23008_is_joystick_up(void);

/* returns 1 if joystick is down, returns 0 if joystick is not down or timeout period has not expired */
bool mcp23008_is_joystick_down(void);

/* returns 1 if joystick is left, returns 0 if joystick is not left or timeout period has not expired */
bool mcp23008_is_joystick_left(void);

/* returns 1 if joystick is right, returns 0 if joystick is not right or timeout period has not expired */
bool mcp23008_is_joystick_right(void);

/* returns 1 if joystick is pressed, returns 0 if joystick is not pressesd or timeout period has not expired */
bool mcp23008_is_joystick_pressed(void);

/* returns 1 if sw1 is pressed, reutrns 0 if sw1 is not pressed or timeout period has not expired */
bool mcp23008_is_sw1_pressed();

/* returns 1 if sw2is pressed, reutrns 0 if sw2 is not pressed or timeout period has not expired */
bool mcp23008_is_sw2_pressed();

/* returns 1 if sw2 is pressed, reutrns 0 if sw2 is not pressed or timeout period has not expired */
bool mcp23008_is_sw3_pressed();

//extern volatile unsigned char joystick_debug;

#ifdef	__cplusplus
}
#endif

#endif	/* MCP23008_H */


