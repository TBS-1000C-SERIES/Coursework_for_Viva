#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "waveform.h"
#include "io.h"

int main() {

    results values;

    RMS_voltage(&values);
    Peak_to_Peak(&values);
    printf("ptp_A: %f\n", values.PtP_A);

    if (CSV_File_Write(&values) == 0) {
        printf("Report generated successfully.\n");
    } else {
        printf("Failed to generate report.\n");
    }

    return 0;
}
