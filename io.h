//
// Created by Zack Webber on 17/04/2026.
//

#ifndef IO_HEADER
#define IO_HEADER
#include <stdio.h>

typedef struct {
    float RMS_A, RMS_B, RMS_C;
    float PtP_A, PtP_B, PtP_C;
    float mean_A, mean_B, mean_C;
} results;

int RMS_voltage(results *values, char *filename);
int Peak_to_Peak(results *values, char *filename);
int Clipping_Detection(FILE *fp, char *filename);
void RMS_Tolerance_Check(FILE *fp, results *values);

int Report_File_Write(results *values, char *filename);

#endif