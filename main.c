#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "waveform.h"
#include "io.h"

int main() {

    results values;

    RMS_voltage(&values);
    Peak_to_Peak(&values);

    if (Report_File_Write(&values) == 0) {
        printf("Quality Report Created Successfully!\n");
    } else {
        printf("Failed to Create Quality Report :(\n");
    }

    return 0;
}