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
#pragma once

/**
 * Arduino Due with RAMPS-SMART pin assignments
 *
 * Applies to the following boards:
 *
 *  RAMPS_SMART_EFB (Hotend, Fan, Bed)
 *  RAMPS_SMART_EEB (Hotend0, Hotend1, Bed)
 *  RAMPS_SMART_EFF (Hotend, Fan0, Fan1)
 *  RAMPS_SMART_EEF (Hotend0, Hotend1, Fan)
 *  RAMPS_SMART_SF  (Spindle, Controller Fan)
 *
 *  Differences between
 *  RAMPS_14 | RAMPS-SMART
 *      NONE | D16 (Additional AUX-3 pin(AUX3_2PIN), shares the same pin with AUX4_18PIN)
 *      NONE | D17 (Additional AUX-3 pin(AUX3_1PIN), shares the same pin with AUX4_17PIN)
 *        D0 | NONE
 *        D1 | NONE
 *    A3/D57 | NONE
 *    A4/D58 | NONE
 *    A5/D59 | A3/D57
 *    A9/D63 | A4/D58
 *   A10/D64 | A5/D59
 *   A11/D65 | D66
 *   A12/D66 | D67
 *       A13 | A9
 *       A14 | A10
 *       A15 | A11
 *
 *
 * REPRAP_DISCOUNT_FULL_GRAPHIC_SMART_CONTROLLER works fine connected to AUX-4 with
 * Smart Adapter, but requires removing the AUX3 pin header on the adapter to fit.
 * To use the SD card reader, wire its pins to AUX-3 (and use Software SPI).
 *
 * To use Hardware SPI for SD, the SDSS pin must be set to 52 instead of 53.
 * Hardware SPI also requires additional wiring because the board doesn't pass
 * the 6-pin SPI header from the DUE board.
 * (Search the web for "Arduino DUE Board Pinout" to see the correct header.)
 */

#define BOARD_INFO_NAME "RAMPS-SMART"
#define ALLOW_SAM3X8E
#include "../ramps/pins_RAMPS.h"

// I2C EEPROM with 4K of space
#define I2C_EEPROM
#define MARLIN_EEPROM_SIZE                0x1000

#define SDA_PIN                               20
#define SCL_PIN                               21

// See EEPROM device datasheet for the following values. These are for 24xx256
#define EEPROM_SERIAL_ADDR                  0x50  // 7 bit i2c address (without R/W bit)
#define EEPROM_PAGE_SIZE                      64  // page write buffer size
#define EEPROM_PAGE_WRITE_TIME                 7  // page write time in milliseconds (docs say 5ms but that is too short)

#define TWI_CLOCK_FREQ                    400000
#define EEPROM_ADDRSZ_BYTES TWI_MMR_IADRSZ_2_BYTE // TWI_MMR_IADRSZ_1_BYTE for 1 byte, or TWI_MMR_IADRSZ_2_BYTE for 2 byte
#define EEPROM_AVAILABLE              EEPROM_I2C

#define RESET_PIN                             42  // Resets the board if the jumper is attached

//
// Temperature Sensors
//
#undef TEMP_0_PIN
#define TEMP_0_PIN                             9  // Analog Input

#undef TEMP_1_PIN
#define TEMP_1_PIN         11   // Analog Input

#undef TEMP_BED_PIN
#define TEMP_BED_PIN       10   // Analog Input

// SPI for MAX Thermocouple
#undef TEMP_0_CS_PIN
#if DISABLED(SDSUPPORT)
  #define TEMP_0_CS_PIN                       67  // Don't use 53 if using Display/SD card
#else
  #define TEMP_0_CS_PIN                       67  // Don't use 49 (SD_DETECT_PIN)
#endif

//
// LCD / Controller
//

// Support for AZSMZ 12864 LCD with SD Card 3D printer smart controller control panel
#if ENABLED(AZSMZ_12864)
  #define BEEPER_PIN                          66  // Smart RAMPS 1.42 pinout diagram on RepRap WIKI erroneously says this should be pin 65
  #define DOGLCD_A0                           59
  #define DOGLCD_CS                           44
  #define BTN_EN1                             58
  #define BTN_EN2                             40
  #define BTN_ENC                             67  // Smart RAMPS 1.42 pinout diagram on RepRap WIKI erroneously says this should be pin 66
  #define SD_DETECT_PIN                       49  // Pin 49 for display sd interface, 72 for easy adapter board
  #define KILL_PIN                            42
#endif
