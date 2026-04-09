//
// Created by Zack Webber on 06/04/2026.
//
#ifndef io
#define io
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Waveform_Structure.h"

inline int CSV_File_Read(void) {

    FILE *fp = fopen("power_quality_log.csv", "r");
    if (fp == NULL) {
        printf("CSV file does not exist\n");
        return 1;
    }                      //checks if file is present and opens it if so


    CSV_Data *Data = (CSV_Data *)malloc(1001 * sizeof(CSV_Data));    //dynamicaly allocated array creation, used so size of dataset can vary

    if (!Data) {
        fprintf(stderr,"Error allocating memory for array\n"); //checks if data is present and can be allocated to the array and daes not return a null pointer
        free(Data);
        return 1;
    }

    char line[256];
    int count = 0;

    fgets(line, sizeof(line), fp);  //excludes column names

    while (fgets(line, sizeof(line), fp) && count < 1001) {   //loops through each line, stopping at the last
        //separating columns

        char *token = strtok(line, ",");      //first column nothing in front, just use strtok(line)
        if (token == NULL) continue;
        float timestamp = atof(token);         // splits and sorts all values to respective column

        token = strtok(NULL, ",");
        float phase_A_voltage = atof(token);

        token = strtok(NULL, ",");
        float phase_B_voltage = atof(token);

        token = strtok(NULL, ",");
        float phase_C_voltage = atof(token);

        token = strtok(NULL, ",");
        float line_current = atof(token);

        token = strtok(NULL, ",");
        float frequency = atof(token);

        token = strtok(NULL, ",");
        float power_factor = atof(token);

        token = strtok(NULL, ",");
        float thd_percent = atof(token);

        count++;      //continues to next line
    }

    if (count >= 350) {
        printf("Row 350 = %f", Data[349].phase_B_voltage);
    }

    fclose(fp);
    free(Data);
    return 0;
}
#endif