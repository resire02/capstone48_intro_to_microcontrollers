/* 
 * File:   veml3328.h
 * Author: howfe
 *
 * Created on March 29, 2025, 2:58 AM
 */

#ifndef VEML3328_H
#define	VEML3328_H

#ifdef	__cplusplus
extern "C" {
#endif

void veml_init();
void veml_read_colors(uint16_t* color);
void veml_read_brightness(uint16_t* brightness);

#ifdef	__cplusplus
}
#endif

#endif	/* VEML3328_H */

