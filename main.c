#include <stdio.h>
#include "io.h"

int main(int argc, char *argv[]) {
    if (argc < 2) return 1;

    results values;

    RMS_voltage(&values, argv[1]);
    Peak_to_Peak(&values, argv[1]);

    if (Report_File_Write(&values, argv[1]) == 0) {
        printf("\nQuality Report Created Successfully!\n");
    } else {
        printf("Failed to Create Quality Report :(\n");
    }

    return 0;
}