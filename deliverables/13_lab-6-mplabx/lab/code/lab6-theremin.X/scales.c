#include "scales.h"
#include "pwm_notes.h"
#include <xc.h>

extern const ScaleBank scale_bank = {
    .c_minor_pentatonic = { {NOTE_C4, NOTE_DS4, NOTE_F4, NOTE_G4, NOTE_AS4}, 5 },
    .c_major_pentatonic = { {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_G4, NOTE_A4}, 5 },
    .c_major = { {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4}, 7 },
    .c_minor = { {NOTE_C4, NOTE_D4, NOTE_DS4, NOTE_F4, NOTE_G4, NOTE_GS4, NOTE_AS4}, 7 }
};