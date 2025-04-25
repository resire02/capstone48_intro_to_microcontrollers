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

#define C_MINOR_PENTATONIC {NOTE_C4, NOTE_DS4, NOTE_F4, NOTE_G4, NOTE_AS4}
#define C_MAJOR_PENTATONIC {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_G4, NOTE_A4}
#define C_MAJOR {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4}    
#define C_MINOR {NOTE_C4, NOTE_D4, NOTE_DS4, NOTE_F4, NOTE_G4, NOTE_GS4, NOTE_AS4}
    
typedef struct {
    float notes[12];
    int length;
} Scale;
    
extern Scale scale_bank[];

extern int num_scales;
    
#ifdef	__cplusplus
}
#endif

#endif	/* SCALES_H */

