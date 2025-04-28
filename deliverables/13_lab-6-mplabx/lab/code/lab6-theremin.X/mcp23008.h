/* 
 * File:   mcp23008.h
 * Author: 
 *
 * Created on April 27, 2025, 3:07 PM
 */

#ifndef MCP23008_H
#define	MCP23008_H

#ifdef	__cplusplus
extern "C" {
#endif
    
/* initializes the MCP23008 IO Expander LEDs */
void mcp23008_init(void);

/* sets the leds on/off */
void mcp23008_write_leds(unsigned char state);

/* reads joystick values */
void mcp23008_read_joystick(void);

int mcp23008_is_joystick_up(void);
int mcp23008_is_joystick_down(void);
int mcp23008_is_joystick_left(void);
int mcp23008_is_joystick_right(void);
int mcp23008_is_joystick_pressed(void);

#ifdef	__cplusplus
}
#endif

#endif	/* MCP23008_H */

