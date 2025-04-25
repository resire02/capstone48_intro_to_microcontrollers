/* 
 * File:   scales.h
 * Author: Gonzalo Allendes
 *
 * Created on 24 de abril de 2025, 10:44
 */

#ifndef SCALES_H
#define	SCALES_H

#ifdef	__cplusplus
extern "C" {
#endif
    
typedef struct {
    float notes[10];
    int length;
} Scale;
    
typedef struct {
    Scale c_minor_pentatonic;
    Scale c_major_pentatonic;
    Scale c_major;
    Scale c_minor;
} ScaleBank;

extern const ScaleBank scale_bank;
    
#ifdef	__cplusplus
}
#endif

#endif	/* SCALES_H */

