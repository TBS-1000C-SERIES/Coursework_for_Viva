#include <stdio.h>
#include "io.h"

int main(int argc, char *argv[]) {      //values to allow function to accept an argument stored as an array of characters
    if (argc < 2) return 1;             //only expecting 2 arguments of argc, one for the program name and one for the argument (filename input)

    results values;                        //called for functions below that need that data

    RMS_voltage(&values, argv[1]);
    Peak_to_Peak(&values, argv[1]);

    if (Report_File_Write(&values, argv[1]) == 0) {         //check that filename was typed in correctly and is present
        printf("\nQuality Report Created Successfully!\n");
    } else {
        printf("\nFailed to Create Quality Report :(\n");
    }

    return 0;
}