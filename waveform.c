//
// Created by Zack Webber on 11/04/2026.
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
         sum_A += pow(ptr->phase_A_voltage, 2);
         sum_B += pow(ptr->phase_B_voltage, 2);
         sum_C += pow(ptr->phase_C_voltage, 2);
    }

    float RMS_A = sqrt(sum_A / count);
    float RMS_B = sqrt(sum_B / count);
    float RMS_C = sqrt(sum_C / count);

    printf("RMS_A = %f\nRMS_B = %f\nRMS_C = %f\n", RMS_A, RMS_B, RMS_C);

    free(main_array);

    return 0;
}