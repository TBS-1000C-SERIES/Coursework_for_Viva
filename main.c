#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Waveform_Structure.h"

int main() {

    RMS_voltage();    //testing function is accessing data correctly
    Clipping_Detection();
    Peak_to_Peak();

    return 0;
}
