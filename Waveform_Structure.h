//
// Created by Zack Webber on 09/04/2026.
//

#ifndef WAVEFORM_STRUCTURE_HEADER
#define	WAVEFORM_STRUCTURE_HEADER

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

CSV_Data* CSV_File_Read(int *count_output);   //data read function has to be declared here so it can be used by other analysis and main functions later

int RMS_voltage(void);    //analysis functions declared here also for a cleaner main
int Clipping_Detection(void);
int Peak_to_Peak(void);

#endif