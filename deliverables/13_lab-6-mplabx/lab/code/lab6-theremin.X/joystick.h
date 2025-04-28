/* 
 * File:   joystick.h
 * Author: kaleb Lenfest
 *
 * Created on April 26, 2025, 11:02 PM
 */

#ifndef JOYSTICK_H
#define	JOYSTICK_H

#ifdef	__cplusplus
extern "C" {
#endif
 
void joystick_init();

bool joystick_left();
bool joystick_right();

#ifdef	__cplusplus
}
#endif

#endif	/* JOYSTICK_H */
