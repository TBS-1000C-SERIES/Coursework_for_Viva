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

    if(!main_array) {
        printf("Error: Cannot access Data");        //file access check
        return 1;
    }

    for (CSV_Data *ptr = main_array; ptr < main_array + count; ptr++) {
         printf("%f\n", ptr->phase_A_voltage);       //test to see if function is accessing data correctly
    }

    free(main_array);

    return 0;
}