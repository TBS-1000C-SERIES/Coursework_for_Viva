//
// Created by Zack Webber on 09/04/2026.
//

#ifndef WAVEFORM_STRUCTURE_HEADER
#define	WAVEFORM_STRUCTURE_HEADER

typedef struct  {                     //structure to store all columns of the data
    double timestamp;
    double phase_A_voltage;
    double phase_B_voltage;
    double phase_C_voltage;
    double line_current;
    double frequency;
    double power_factor;
    double thd_percent;
} CSV_Data;

CSV_Data* CSV_File_Read(char *filename, int *count_output);   //data read function has to be declared here so it can be used by other analysis and main functions later

#endif