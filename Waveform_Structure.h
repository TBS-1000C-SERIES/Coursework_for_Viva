//
// Created by Zack Webber on 09/04/2026.
//

#ifndef waveform_sample
#define	waveform_sample

typedef struct  {
    float timestamp;
    float phase_A_voltage;
    float phase_B_voltage;
    float phase_C_voltage;
    float line_current;
    float frequency;
    float power_factor;
    float thd_percent;
} CSV_Data;

#endif