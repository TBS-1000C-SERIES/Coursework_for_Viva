#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Waveform_Structure.h"

int main() {

    int CSV_File_Read(void); {

        FILE *fp = fopen("power_quality_log.csv", "r");
        if (fp == NULL) {
            printf("CSV file does not exist\n");
            return 1;
        }                      //checks if file is present and opens it if so


        CSV_Data *Data = (CSV_Data *)malloc(1001 * sizeof(CSV_Data));    //dynamically allocated array creation, used so size of dataset can vary

        if (!Data) {
            fprintf(stderr,"Error allocating memory for array\n"); //checks if data is present and can be allocated to the array and does not return a null pointer
            free(Data);
            return 1;
        }

        char line[256];
        int count = 0;

        fgets(line, sizeof(line), fp);  //excludes column names

        while (fgets(line, sizeof(line), fp) && count < 1001) {   //loops through each line, stopping at the last

            char *token = strtok(line, ",");         //separating values by detecting commas as tokens

            if (token == NULL) continue;                 // splits first value by commas
            Data[count].timestamp = atof(token);         // assigns split string to respective float value with atof in array

            token = strtok(NULL, ",");                   //repeates for all floats in that line
            Data[count].phase_A_voltage = atof(token);

            token = strtok(NULL, ",");
            Data[count].phase_B_voltage = atof(token);

            token = strtok(NULL, ",");
            Data[count].phase_C_voltage = atof(token);

            token = strtok(NULL, ",");
            Data[count].line_current = atof(token);

            token = strtok(NULL, ",");
            Data[count].frequency = atof(token);

            token = strtok(NULL, ",");
            Data[count].power_factor = atof(token);

            token = strtok(NULL, ",");
            Data[count].thd_percent = atof(token);

            count++;      //continues to next line
        }

        {
            printf("Row 367 = %f", Data[367-2].phase_A_voltage);        //testing with random line
        }

        fclose(fp);
        free(Data);
        return 0;
    }


}