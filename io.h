//
// Created by Zack Webber on 06/04/2026.
//
#ifndef io
#define io
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

inline int CSV_File_Read(void) {
    FILE *fp = fopen("power_quality_log.csv", "r");
    if (fp == NULL) {
        printf("CSV file does not exist\n");
        return 1;
    }                      //checks if file is present and opens it if so
    char line[256];

    fgets(line, sizeof(line), fp);  //excludes column names

    while (fgets(line, sizeof(line), fp) != NULL) {    //separating columns

        char *token = strtok(line, ",");      //first column nothing in front, just use strtok(line)
        if (token == NULL) continue;
        float timestamp = atof(token);

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

        printf("timestamp = %f, phase_A_voltage = %f, phase_B_voltage = %f, phase_C_voltage = %f, line_current = %f, frequency = %f, power_factor = %f, thd_percent = %f\n",
               timestamp, phase_A_voltage, phase_B_voltage, phase_C_voltage, line_current, frequency, power_factor, thd_percent);
    }
    fclose(fp);
    return 0;
}
#endif