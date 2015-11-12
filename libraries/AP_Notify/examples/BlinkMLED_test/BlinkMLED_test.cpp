// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: t -*-

#include <AP_Common/AP_Common.h>
#include <AP_Progmem/AP_Progmem.h>
#include <AP_Math/AP_Math.h>            // ArduPilot Mega Vector/Matrix math Library
#include <AP_Param/AP_Param.h>
#include <Filter/Filter.h>
#include <AP_ADC/AP_ADC.h>
#include <AP_InertialSensor/AP_InertialSensor.h>
#include <AP_GPS/AP_GPS.h>
#include <AP_Baro/AP_Baro.h>
#include <DataFlash/DataFlash.h>
#include <GCS_MAVLink/GCS_MAVLink.h>
#include <AP_Mission/AP_Mission.h>
#include <StorageManager/StorageManager.h>
#include <AP_Terrain/AP_Terrain.h>
#include <AP_Declination/AP_Declination.h>
#include <AP_HAL/AP_HAL.h>
#include <AP_HAL_AVR/AP_HAL_AVR.h>
#include <AP_HAL_SITL/AP_HAL_SITL.h>
#include <AP_HAL_Linux/AP_HAL_Linux.h>
#include <AP_HAL_PX4/AP_HAL_PX4.h>
#include <AP_HAL_Empty/AP_HAL_Empty.h>
#include <AP_HAL_FLYMAPLE/AP_HAL_FLYMAPLE.h>
#include <AP_Notify/AP_Notify.h>          // Notify library
#include <AP_AHRS/AP_AHRS.h>
#include <AP_NavEKF/AP_NavEKF.h>
#include <AP_Airspeed/AP_Airspeed.h>
#include <AP_Vehicle/AP_Vehicle.h>
#include <AP_ADC_AnalogSource/AP_ADC_AnalogSource.h>
#include <AP_Compass/AP_Compass.h>
#include <AP_Declination/AP_Declination.h>
#include <AP_BattMonitor/AP_BattMonitor.h>
#include <AP_RangeFinder/AP_RangeFinder.h>

const AP_HAL::HAL& hal = AP_HAL_BOARD_DRIVER;

static BlinkMLED_I2C blinkm_led;
static uint8_t counter, step;

void setup(void)
{
    // display welcome message
    hal.console->print_P(PSTR("BlinkM LED test ver 0.1\n"));

    // initialise LED
	blinkm_led.init();

    // check if healthy
    if (!blinkm_led.healthy()) {
        hal.console->print_P(PSTR("Failed to initialise BlinkM LED\n"));
    }

    hal.console->print_P(PSTR("Setup BlinkM LED\n"));

    // turn on initialising notification
	// AP_Notify::flags.initialising = true;
    // AP_Notify::flags.save_trim = false;
    // AP_Notify::flags.gps_status = 0;
	// AP_Notify::flags.armed = 0;
    // AP_Notify::flags.pre_arm_check = 1;
	// blinkm_led.set_override_pattern(LED_SET_COLOUR_PATTERN_SOLID);
	blinkm_led.set_override_pattern(LED_SET_COLOUR_PATTERN_FADEOUT);
    counter = 0;
    step = 0;
}

// full_spectrum - runs through the full spectrum of colours the led can display
void full_spectrum()
{
    // go through the full range of colours but only up to the dim light level
    for (uint8_t red=0; red<=0x05; red++) {
        for (uint8_t green=0; green<=0x05; green++) {
            for (uint8_t blue=0; blue<=0x05; blue++) {
                blinkm_led.set_rgb(red,green,blue);
                hal.scheduler->delay(5);
            }
        }
    }
}

void blink()
{
    counter++;
    if (counter < 100) {
        return;
    }

    // reset counter
    counter = 0;

    hal.console->print(step);
	blinkm_led.set_override_pattern(LED_SET_COLOUR_PATTERN_FADEOUT);
    // full spectrum test
    if (step==0) {
        blinkm_led.set_rgb(BLINKMLED_BRIGHT,0,0);   // red
    } else if (step==1) {
        blinkm_led.set_rgb(0,BLINKMLED_BRIGHT,0);   // green
    } else if (step==2) {
        blinkm_led.set_rgb(0,0,BLINKMLED_BRIGHT);   // blue
    } else {
        blinkm_led.set_rgb(BLINKMLED_BRIGHT,BLINKMLED_BRIGHT,BLINKMLED_BRIGHT);   // white
    }
    step++;
    if (step > 3) {
        step = 0;
    }
}

void loop(void)
{
    // blink test
    // hal.console->print_P(PSTR("Blink test\n"));
    blink();

    // full spectrum test
    // hal.console->print_P(PSTR("Spectrum test\n"));
    // full_spectrum();

    // update the blinkm led
    blinkm_led.update();

    // wait 1/50th of a second
    hal.scheduler->delay(20);
}

AP_HAL_MAIN();
