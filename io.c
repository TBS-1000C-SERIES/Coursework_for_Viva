//
// Created by Zack Webber on 06/04/2026.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "waveform.h"
#include "io.h"

CSV_Data *CSV_File_Read(char *filename, int *count_output) {     //output is a pointer parameter as function needs to return the number of rows as well as the array

        FILE *fp = fopen(filename, "r");
        if (fp == NULL) {
            fprintf(stderr, "CSV file does not exist\n");        //checks if file is present and opens it if so

            if (count_output != NULL) *count_output = 0;       //checks count is set to 0 to prevent any "runaway loops"
            return NULL;
        }

        CSV_Data *main_array = malloc(999 * sizeof(CSV_Data));    //dynamically allocated array creation, used so size of dataset can vary

        if (main_array == NULL) {
            perror("Error allocating memory for array\n");     //checks if data is present and can be allocated to the array and does not return a null pointer
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

            token = strtok(NULL, ",");
            if (token == NULL) continue;                 //adding null check to every parameter
            main_array[count].phase_A_voltage = atof(token);    //assigns it to the structure

            token = strtok(NULL, ",");                      //repeats for all columns
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

int Report_File_Write(results *values, char *filename) {      //report write calling assigned values and the filename pointer

    int count;
    CSV_Data *main_array = CSV_File_Read(filename, &count);

    if (main_array == NULL) {                               //file access check
        return 1;
    }

    FILE *fp = fopen("Quality_report.txt", "w");          //creating text document

    if (fp == NULL) {
        free(main_array);
        return 1;
    }
    fprintf(fp, "=================================\n");     //writing/formatting of report file in a need way with all important metrics form the results struct.
    fprintf(fp, "     WAVEFORM QUALITY REPORT\n");
    fprintf(fp, "=================================\n");
    RMS_Tolerance_Check(fp, values);                       //calling function from waveform as file is being written to from there instead
    fprintf(fp, "\nRoot Mean Square Voltage's\n");
    fprintf(fp, "--------------------------\n");
    fprintf(fp, "\nPhase A: %f\n", values->RMS_A);
    fprintf(fp, "Phase B: %f\n", values->RMS_B);
    fprintf(fp, "Phase C: %f\n", values->RMS_C);
    fprintf(fp, "\nDC Offset's\n");
    fprintf(fp, "-----------\n");
    fprintf(fp, "\nPhase A: %f\n", values->mean_A);
    fprintf(fp, "Phase B: %f\n", values->mean_B);
    fprintf(fp, "Phase C: %f\n", values->mean_C);
    fprintf(fp, "\nPeak to Peak Voltage's\n");
    fprintf(fp, "----------------------\n");
    fprintf(fp, "\nPhase A: %f\n", values->PtP_A);
    fprintf(fp, "Phase B: %f\n", values->PtP_B);
    fprintf(fp, "Phase C: %f\n", values->PtP_C);
    fprintf(fp, "\nPoints out of Sensor Hard Limit (324.9V)\n");
    fprintf(fp, "---------------------------------------\n");
    Clipping_Detection(fp, filename);
    fprintf(fp, "\n\n=================================\n");
    fprintf(fp, "         END OF REPORT\n");
    fprintf(fp, "=================================");

    fclose(fp);
    free(main_array);

    return 0;
}