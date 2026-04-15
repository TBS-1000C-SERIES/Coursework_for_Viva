//
// Created by Zack Webber on 13/04/2026.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Waveform_Structure.h"

int RMS_voltage(void) {

    int count;
    CSV_Data *main_array = CSV_File_Read(&count);    //calling file read function

    float sum_A, sum_B, sum_C;                    //individual sums for each phase
    sum_A = sum_B = sum_C = 0;

    if(main_array == NULL) {
        printf("Error: Cannot access Data");        //file access check
        return 1;
    }

    for (CSV_Data *ptr = main_array; ptr < main_array + count; ptr++) {
        sum_A += ptr->phase_A_voltage;
        sum_B += ptr->phase_B_voltage;
        sum_C += ptr->phase_C_voltage;
    }

    float mean_A = sum_A / count;
    float mean_B = sum_B / count;
    float mean_C = sum_C / count;

    printf("mean_A = %f\nmean_B = %f\nmean_C = %f\n", mean_A, mean_B, mean_C);

    for (CSV_Data *ptr = main_array; ptr < main_array + count; ptr++) {
         sum_A += pow(ptr->phase_A_voltage, 2);
         sum_B += pow(ptr->phase_B_voltage, 2);
         sum_C += pow(ptr->phase_C_voltage, 2);
    }

    float RMS_A = sqrt(sum_A / count);
    float RMS_B = sqrt(sum_B / count);
    float RMS_C = sqrt(sum_C / count);

    if(RMS_A >= 207 && RMS_A <= 253) {
        printf("Phase A .... Nominal\n");
    }
    else {
         printf("Phase A .... Outside Acceptable Range!\n");
    }

    if(RMS_B >= 207 && RMS_B <= 253) {
        printf("Phase B .... Nominal\n");
    }
    else {
        printf("Phase B .... Outside Acceptable Range!\n");
    }

    if(RMS_C >= 207 && RMS_C <= 253) {
        printf("Phase C .... Nominal\n");
    }
    else {
        printf("Phase C .... Outside Acceptable Range!\n");
    }

    printf("RMS_A = %f\nRMS_B = %f\nRMS_C = %f\n", RMS_A, RMS_B, RMS_C);

    free(main_array);

    return 0;
}

int Amplitude(void) {

}