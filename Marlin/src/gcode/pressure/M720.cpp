//Custom code to run the pressure sensor amplified using the HX710B

#include "../../inc/MarlinConfigPre.h"
#include "../gcode.h"
#include "../../pressure/HX710AB.h"

HX710B pressure_sensor(HX710B_OUT_PIN, HX710B_SCK_PIN);
uint32_t time_update = 0;

void GcodeSuite::M720(){
    
}