#include <stdio.h>
#include "io.h"

int main(int argc, char *argv[]) {      //values to allow function to accept an argument stored as an array of characters
    if (argc < 2) return 1;             //only expecting 2 arguments of argc, one for the program name and one for the argument (filename input)

    results values;                        //called for functions below that need to assign data to it

    RMS_voltage(&values, argv[1]);         //these function are returning values being assigned to the results structure so need to be called here and given the filename in form argv[1]
    Peak_to_Peak(&values, argv[1]);        //clipping detection and tolerance check are being printed form waveform.c directly into the file so do not need to be called

    if (Report_File_Write(&values, argv[1]) == 0) {         //check that filename was typed in correctly and is present and reports back 0 == 0(success) or 1 == 0 (failure)
        printf("\nQuality Report Created Successfully!\n");
    } else {
        printf("\nFailed to Create Quality Report :(\n");
    }

    return 0;
}