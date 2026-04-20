//
// Created by Zack Webber on 13/04/2026.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "waveform.h"
#include "io.h"

int RMS_voltage(results *values, char *filename) {

    int count;
    CSV_Data *main_array = CSV_File_Read(filename, &count);    //calling file read function

    float sum_A, sum_B, sum_C;                    //individual sums for each phase
    sum_A = sum_B = sum_C = 0;

    if(main_array == NULL) {     //file access check
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

    for (CSV_Data *ptr = main_array; ptr < main_array + count; ptr++) {
         sum_A += pow(ptr->phase_A_voltage, 2);
         sum_B += pow(ptr->phase_B_voltage, 2);
         sum_C += pow(ptr->phase_C_voltage, 2);
    }

    float RMS_A = sqrt(sum_A / count);
    float RMS_B = sqrt(sum_B / count);
    float RMS_C = sqrt(sum_C / count);

    values->RMS_A = RMS_A;
    values->RMS_B = RMS_B;
    values->RMS_C = RMS_C;
    values->mean_A= mean_A;
    values->mean_B = mean_B;
    values->mean_C = mean_C;

    free(main_array);

    return 0;
}

void RMS_Tolerance_Check(FILE *fp, results *values) {

    if(values->RMS_A >= 207 && values->RMS_A <= 253) {
        fprintf(fp, "\nPhase A .... Nominal\n");
    }
    else {
        fprintf(fp, "Phase A .... Outside Acceptable Range!\n");
    }

    if(values->RMS_B >= 207 && values->RMS_B <= 253) {
        fprintf(fp, "Phase B .... Nominal\n");
    }
    else {
        fprintf(fp, "Phase B .... Outside Acceptable Range!\n");
    }

    if(values->RMS_C >= 207 && values->RMS_C <= 253) {
        fprintf(fp, "Phase C .... Nominal\n");
    }
    else {
        fprintf(fp, "Phase C .... Outside Acceptable Range!\n");
    }
}

int Clipping_Detection(FILE *fp, char *filename) {

    int count;
    CSV_Data *main_array = CSV_File_Read(filename, &count);    //calling file read function

    if(main_array == NULL) {     //file access check
        return 1;
    }

    int line_A, line_B, line_C; // starting point for line numbers, starts at 2 because we skip the header and C starts counting at 0 not 1
    line_A = line_B = line_C = 2;

    int clipping_A, clipping_B, clipping_C;    // individual clipping zeros for each phase
    clipping_A = clipping_B = clipping_C = 0;  // 0 = false, meaning no clipping detected

    for (CSV_Data *ptr = main_array; ptr < main_array + count; ptr++, line_A++) {
        if(ptr->phase_A_voltage >= 324.9 || ptr->phase_A_voltage <= -324.9) {  // checks if value is within parameters
            if (clipping_A == 0) {
                fprintf(fp, "\nPhase A clipping detected at lines: ");    //if a clipping value is found, prints this opening statement
                clipping_A = 1;
            }
            fprintf(fp, "%d, ", line_A);     // adds on all subsequent instances found as loop continues
        }
    }
    for (CSV_Data *ptr = main_array; ptr < main_array + count; ptr++, line_B++) {     //same loop pass for each phase
        if(ptr->phase_B_voltage >= 324.9 || ptr->phase_B_voltage <= -324.9) {
            if (clipping_B == 0) {
                fprintf(fp, "\nPhase B clipping detected at lines: ");
                clipping_B = 1;
            }
            fprintf(fp, "%d, ", line_B);
        }
    }
    for (CSV_Data *ptr = main_array; ptr < main_array + count; ptr++, line_C++) {
        if(ptr->phase_C_voltage >= 324.9 || ptr->phase_C_voltage <= -324.9) {
            if (clipping_C == 0) {
                fprintf(fp, "\nPhase C clipping detected at lines: ");
                clipping_C = 1;
            }
            fprintf(fp, "%d, ", line_C);
        }
    }

    free(main_array);

    return 0;
}

int Peak_to_Peak(results *values, char *filename) {

    int count;
    CSV_Data *main_array = CSV_File_Read(filename, &count);    //calling file read function

    if(main_array == NULL) {     //file access check
        return 1;
    }

    float max_A , max_B, max_C, min_A, min_B, min_C;
    max_A = max_B = max_C = min_A = min_B = min_C = 0;            //initialises variables and the start point

    for (CSV_Data *ptr = main_array; ptr < main_array + count; ptr++) {
         if(ptr->phase_A_voltage >= max_A) {
             max_A = ptr->phase_A_voltage ;
         }else if(ptr->phase_A_voltage <= min_A) {                //loop to trial-and-error the values for min and max my going through and setting the closest match for each
             min_A = ptr->phase_A_voltage;
         }
    }
    float PtP_A = max_A - min_A;                            //calculates final peak to peak value

    for (CSV_Data *ptr = main_array; ptr < main_array + count; ptr++) {      //process is replicated for each phase
        if(ptr->phase_B_voltage >= max_B) {
            max_B = ptr->phase_B_voltage ;
        }else if(ptr->phase_B_voltage <= min_B) {
            min_B = ptr->phase_B_voltage;
        }
    }
    float PtP_B = max_B - min_B;

    for (CSV_Data *ptr = main_array; ptr < main_array + count; ptr++) {
        if(ptr->phase_C_voltage >= max_C) {
            max_C = ptr->phase_C_voltage ;
        }else if(ptr->phase_C_voltage <= min_C) {
            min_C = ptr->phase_C_voltage;
        }
    }
    float PtP_C = max_C - min_C;

    values->PtP_A = PtP_A;
    values->PtP_B = PtP_B;
    values->PtP_C = PtP_C;

    free(main_array);

    return 0;
}