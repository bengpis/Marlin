#include "../../pressure/HX710AB.h"
#include "../gcode.h"
#include "../../core/serial.h"

void GcodeSuite::M720() {
// Initialize pins using Marlin's macros
//
//    FILE: HX710B_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
//     URL: https://github.com/RobTillaart/HX710AB


    #define M720_DATA_PIN   50
    #define M720_CLOCK_PIN  52

    HX710A hx(M720_DATA_PIN, M720_CLOCK_PIN);


    static bool inited = false;
    if (!inited) {
        hx.begin();
        inited = true;
    }

    // Normal channel
    int32_t value = hx.read(false);
    SERIAL_ECHO_START();
    SERIAL_ECHOPGM("HX710B VALUE: ", value);
    SERIAL_EOL();

    // DVDD channel
    value = hx.read(true);
    SERIAL_ECHO_START();
    SERIAL_ECHOPGM("HX710B DVDD: ", value);
    SERIAL_EOL();
}

  
