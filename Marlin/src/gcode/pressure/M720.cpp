/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include "../gcode.h"
#include "../../../src/module/HX710AB/HX710AB.h"

// Define pins for your setup (adjust as needed)
#define HX710B_DATA_PIN 50
#define HX710B_CLOCK_PIN 52

// Create a static HX710B instance so it persists between calls
static HX710B hx710b(HX710B_DATA_PIN, HX710B_CLOCK_PIN);
static bool hx710b_initialized = false;

void GcodeSuite::M720() {
  if (!hx710b_initialized) {
    hx710b.begin();
    // Adjust calibration to your raw measurements
    hx710b.calibrate(-4000000, 0, -8388608, 40);
    hx710b_initialized = true;
  }

  // Read the calibrated value (change argument if needed)
  float vacuum = hx710b.read(1);
  float vacuum_kPa = hx710b.get_units(10);

  // Report the value in a Marlin-style response
  SERIAL_ECHO_START();
  SERIAL_ECHO("RAW: ", vacuum);
  SERIAL_ECHO("Vacuum (kPa): ", vacuum_kPa);
  SERIAL_EOL();
}