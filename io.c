//
// Created by Zack Webber on 06/04/2026.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Waveform_Structure.h"

CSV_Data *CSV_File_Read(int *count_output) {     //output is a pointer parameter as function needs to return the number of rows as well as the array

        FILE *fp = fopen("power_quality_log.csv", "r");
        if (fp == NULL) {
            printf("CSV file does not exist\n");
            return NULL;
        }                      //checks if file is present and opens it if so


        CSV_Data *main_array = malloc(999 * sizeof(CSV_Data));    //dynamically allocated array creation, used so size of dataset can vary

        if (main_array == NULL) {
            fprintf(stderr,"Error allocating memory for array\n"); //checks if data is present and can be allocated to the array and does not return a null pointer
            fclose(fp);
            return NULL;
        }

        char line[256];
        int count = 0;

        fgets(line, sizeof(line), fp);  //excludes column names

        while (fgets(line, sizeof(line), fp) && count < 999) {   //loops through each line, stopping at the last

            char *token = strtok(line, ",");         //separating values by detecting commas as tokens
            if (token == NULL) continue;                 //checks if token is null before continuing so values don't become zero
            main_array[count].timestamp = atof(token);         // assigns split string to respective float value with atof in array

            token = strtok(NULL, ",");                   //repeats for all floats in that line
            if (token == NULL) continue;                 //adding null check to every parameter    15/04
            main_array[count].phase_A_voltage = atof(token);

            token = strtok(NULL, ",");
            if (token == NULL) continue;
            main_array[count].phase_B_voltage = atof(token);

            token = strtok(NULL, ",");
            if (token == NULL) continue;
            main_array[count].phase_C_voltage = atof(token);

            token = strtok(NULL, ",");
            if (token == NULL) continue;
            main_array[count].line_current = atof(token);

            token = strtok(NULL, ",");
            if (token == NULL) continue;
            main_array[count].frequency = atof(token);

            token = strtok(NULL, ",");
            if (token == NULL) continue;
            main_array[count].power_factor = atof(token);

            token = strtok(NULL, ",");
            if (token == NULL) continue;
            main_array[count].thd_percent = atof(token);

            count++;      //continues to next line
        }

        fclose(fp);         //closes file

    *count_output = count;  //assigning collected count from here's address to a pointer so it can be accessed in analysis functions

    return main_array;      //returning main_array instead of 0 so it can m be used in analysis functions
    }