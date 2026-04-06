//
// Created by Zack Webber on 06/04/2026.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int CSV_File_Read(void) {       //opens file
    FILE *fp = fopen("power_quality_log.csv", "r");
    if (fp == NULL) {
        printf("CVS file does not exist\n");
        return 1;
    }
    char line[256];

    fgets(line, sizeof(line), fp);  //excludes column names

    while (fgets(line, sizeof(line), fp) != NULL) {    //separate columns
        char *token;

        token = strtok(line, ",");
        float timestamp = atof(token);

        token = strtok(line, ",");
        float phase_A_voltage = atof(token);

        token = strtok(line, ",");
        float phase_B_voltage = atof(token);

        token = strtok(line, ",");
        float phase_C_voltage = atof(token);

        token = strtok(line, ",");
        float line_current = atof(token);

        token = strtok(line, ",");
        float frequency = atof(token);

        token = strtok(line, ",");
        float power_factor = atof(token);

        token = strtok(line, ",");
        float thd_percent = atof(token);

        printf("timestamp = %f, phase_A_voltage = %f, phase_B_voltage = %f, phase_C_voltage = %f, line_current = %f, frequency = %f, power_factor = %f, thd_percent = %f\n",
        timestamp, phase_A_voltage, phase_B_voltage, phase_C_voltage, line_current, frequency, power_factor, thd_percent);
    }
    fclose(fp);
    return 0;
}