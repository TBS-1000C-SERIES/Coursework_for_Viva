//
// Created by Zack Webber on 17/04/2026.
//

#ifndef IO_HEADER
#define IO_HEADER

typedef struct {
    float RMS_A, RMS_B, RMS_C;
    float PtP_A, PtP_B, PtP_C;
    float mean_A, mean_B, mean_C;
} results;

void RMS_voltage(results *values);
void Peak_to_Peak(results *values);

int CSV_File_Write(results *values);




#endif