#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "waveform.h"
#include "io.h"

int main() {

       //testing function is accessing data correctly
    Clipping_Detection();
    Peak_to_Peak();

    results values;

    RMS_voltage(&values);
    printf("RMS_A: %f\n", values.RMS_A);

    if (CSV_File_Write(&values) == 0) {
        printf("Report generated successfully.\n");
    } else {
        printf("Failed to generate report.\n");
    }

    return 0;
}
