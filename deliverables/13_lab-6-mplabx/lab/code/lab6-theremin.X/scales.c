/*
 * File:   scales.c
 * Author: Gonzalo Allendes
 *
 * Created on 24 de abril de 2025, 10:44
 */
#include "scales.h"
#include "pwm_notes.h"
#include <xc.h>

Scale scale_bank[] = {
    { C_MINOR_PENTATONIC, 5 },
    { C_MAJOR_PENTATONIC, 5 },
    { C_MAJOR, 7 },
    { C_MINOR, 7 },
    { C_MINOR_BLUES, 6 },
    { C_SEN, 5 }
};

int num_scales = sizeof(scale_bank) / sizeof(scale_bank[0]);