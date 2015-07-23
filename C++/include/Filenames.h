/* 
 * File:   Filenames.h
 * Author: Richard Greene
 * 
 * Names of named pipes and other shared files.
 *
 * Created on May 19, 2014, 11:17 AM
 */

#ifndef FILENAMES_H
#define	FILENAMES_H

#include <Shared.h>

#define CAPE_MANAGER_SLOTS_FILE ("/sys/devices/bone_capemgr.9/slots")
#define BOARD_SERIAL_NUM_FILE ("/sys/bus/i2c/devices/0-0050/eeprom")
#define THERMOMETER_FILE ("/mnt/1wire/22.*/temperature")
#define GPIO_VALUE ("/sys/class/gpio/gpio%d/value")
#define GPIO_DIRECTION ("/sys/class/gpio/gpio%d/direction")
#define GPIO_EDGE ("/sys/class/gpio/gpio%d/edge")
#define GPIO_EXPORT ("/sys/class/gpio/export")
#define GPIO_UNEXPORT ("/sys/class/gpio/unexport")
#define UUID_FILE "/proc/sys/kernel/random/uuid"

#define PRINTER_STATUS_PIPE ("/tmp/PrinterStatusPipe")

#define SLICE_IMAGE_EXTENSION "png"
#define SLICE_IMAGE_FILE_FILTER ("/*." SLICE_IMAGE_EXTENSION)

#define PRINT_FILE_FILTER_TARGZ "/*.tar.gz"
#define PRINT_FILE_FILTER_ZIP "/*.zip"

#define SLICE_IMAGE_PREFIX "slice_"

#define TEST_PATTERN_FILE "/TestPattern.png"
#define TEST_PATTERN (ROOT_DIR TEST_PATTERN_FILE)

#define CAL_IMAGE_FILE "/Calibration.png"
#define CAL_IMAGE (ROOT_DIR CAL_IMAGE_FILE)

#define EMBEDDED_PRINT_SETTINGS_FILE "/printsettings"
#define PER_LAYER_SETTINGS_FILE "/layersettings.csv"

#endif	/* FILENAMES_H */