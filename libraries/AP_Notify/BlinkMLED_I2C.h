/*
   BlinkMLED I2C driver

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef __BLINKMLED_I2C_H__
#define __BLINKMLED_I2C_H__

// #include <AP_HAL/AP_HAL.h>
#include "NotifyDevice.h"
// #include "RGBLed.h"

#define BLINKMLED_CMD_LENGTH_MAX    70

#define BLINKMLED_NUM_INSTANCES     4       // maximum number of individual LEDs connected to I2C
#define BLINKMLED_ALL_INSTANCES     0xff    // instance number to indicate all LEDs

#define BLINKMLED_ADDRESS           0x09    // default I2C bus address
#define BLINKMLED_ADDRESS_ALL       0x00    // I2C "general call" broadcast address. Use this to controll all instances on the bus
#define BLINKMLED_SUBADDR_ALL       0x00    // just for clarity
#define BLINKMLED_SUBADDR_READONLY  0x00    // just for clarity
#define BLINKMLED_SUBADDR_BLUE      0x01    // pwm0 register without auto-increment
#define BLINKMLED_SUBADDR_GREEN     0x02    // pwm1 register without auto-increment
#define BLINKMLED_SUBADDR_RED       0x03    // pwm2 register without auto-increment
#define BLINKMLED_SUBADDR_ENABLE    0x04    // enable register without auto-increment

#define BLINKMLED_POWERSAVE_OFF     0x01    // power-save mode is not off when HIGH
#define BLINKMLED_ENABLE            0x02    // LED is on
#define BLINKMLED_FULLPOWER_ENABLE BLINKMLED_POWERSAVE_OFF | BLINKMLED_ENABLE

#define BLINKMLED_BRIGHT  0xFF    // full brightness
#define BLINKMLED_MEDIUM  0x80    // medium brightness
#define BLINKMLED_DIM     0x11    // dim
#define BLINKMLED_OFF     0x00    // off

class BlinkMLED_I2C : public NotifyDevice
{
public:
    BlinkMLED_I2C();
    // bool hw_init(void);
    // bool hw_set_rgb(uint8_t r, uint8_t g, uint8_t b);
    bool init(void);
    virtual bool healthy() { return _healthy; }
    bool set_rgb(uint8_t r, uint8_t g, uint8_t b);
    uint8_t set_override_pattern(uint8_t pattern_id);
    // void handle_led_control(mavlink_message_t *msg);
    void handle_led_set_colour(mavlink_message_t *msg);
    void update();
private:
    // holds last processed pattern override ID, 0 if we are not overriding a pattern
    uint8_t _override_pattern_id;
    uint8_t _pattern_counter;
    uint8_t _pattern_brightness;
    uint8_t _red_curr, _green_curr, _blue_curr;  // current colours displayed by the led
    bool _healthy;                               // true if the LED is operating properly
};

#endif // __BLINKMLED_I2C_H__
