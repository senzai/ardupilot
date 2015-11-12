/*
  BlinkMLED I2C driver
  Author: Goro Senzai <goro@lambdrive.net>
*/
/*
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

#include "BlinkMLED_I2C.h"

extern const AP_HAL::HAL& hal;

BlinkMLED_I2C::BlinkMLED_I2C():
    _override_pattern_id(0),
    _pattern_counter(0),
    _pattern_brightness(0xff),
    _red_curr(0),
    _green_curr(0),
    _blue_curr(0),
    _healthy(true)
{

}

bool BlinkMLED_I2C::init()
{
    _pattern_brightness = BLINKMLED_BRIGHT;

    // get pointer to i2c bus semaphore
    AP_HAL::Semaphore* i2c_sem = hal.i2c->get_semaphore();

    // take i2c bus sempahore
    if (!i2c_sem->take(HAL_SEMAPHORE_BLOCK_FOREVER)) {
        return false;
    }

    // disable recording of i2c lockup errors
    hal.i2c->ignore_errors(true);

    bool ret = false;

    uint8_t no_script_at_startup[] = {'B',0,0,0,0,0}; // This resets all variables including fade speed.
    uint8_t no_script_result = hal.i2c->write(BLINKMLED_ADDRESS, sizeof(no_script_at_startup), &no_script_at_startup[0]);

    if (no_script_result == 0) {
      hal.console->print_P(PSTR("Disabled BlinkM LED Startup Script\n"));
      ret = true;
    } else {
      hal.console->print_P(PSTR("Couldn't Disable BlinkM LED Startup Script\n"));
    }

    uint8_t stop_script[] = {'o'};
    uint8_t stop_script_result = hal.i2c->write(BLINKMLED_ADDRESS, sizeof(stop_script), &stop_script[0]);

    uint8_t set_fade_speed[] = {'f',5}; // speed must be 1-255. 1 = slowest. 255 = fastest. 0 is reserved.
    uint8_t set_fade_speed_result = hal.i2c->write(BLINKMLED_ADDRESS, sizeof(set_fade_speed), &set_fade_speed[0]);

	// Initial state = black
    uint8_t black_now[4] = { 'n', 0, 0, 0 };
    uint8_t result = hal.i2c->write(BLINKMLED_ADDRESS, sizeof(black_now), &black_now[0]);

    // re-enable recording of i2c lockup errors
    hal.i2c->ignore_errors(false);

    // give back i2c semaphore
    i2c_sem->give();

    return ret;
}

// set_rgb - set colour as a combination of red, green and blue values
bool BlinkMLED_I2C::set_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
    // get pointer to i2c bus semaphore
    AP_HAL::Semaphore* i2c_sem = hal.i2c->get_semaphore();

    // exit immediately if we can't take the semaphore
    if (i2c_sem == NULL || !i2c_sem->take(5)) {
        return false;
    }

    uint8_t rgb_now[] = { 'n', red, green, blue };
    uint8_t result = hal.i2c->write(BLINKMLED_ADDRESS, sizeof(rgb_now), &rgb_now[0]);

    switch (BlinkMLED_I2C::_override_pattern_id) {
      case LED_SET_COLOUR_PATTERN_OFF:
      {
        uint8_t black_now[] = { 'n', 0, 0, 0 };
        result &= hal.i2c->write(BLINKMLED_ADDRESS, sizeof(black_now), &black_now[0]);
        break;
      }
      case LED_SET_COLOUR_PATTERN_FADEOUT:
      {
        uint8_t fadeout_msg[] = { 'c', 0, 0, 0 }; // fade to black
        result &= hal.i2c->write(BLINKMLED_ADDRESS, sizeof(fadeout_msg), &fadeout_msg[0]);
        break;
      }
      default:
        break;
    }

    bool success = (result == 0);

    // give back i2c semaphore
    i2c_sem->give();

    return success;
}

uint8_t BlinkMLED_I2C::set_override_pattern(uint8_t pattern_id) {
    _pattern_counter = 0;
    _pattern_brightness = 0xff;
    _override_pattern_id = pattern_id;

    // get pointer to i2c bus semaphore
    AP_HAL::Semaphore* i2c_sem = hal.i2c->get_semaphore();

    // take i2c bus sempahore
    if (!i2c_sem->take(HAL_SEMAPHORE_BLOCK_FOREVER)) {
        return false;
    }

	// BlinkM preset fade pattern ID copied from BlinkM datasheet.
	// Not used in this implementation. Just for future reference.
	//  0: eeprom script default startup: white→red→green→blue→off (can be reprogrammed)
	//  1: RGB: red→green→blue
	//  2: white flash: white→off
	//  3: red flash: red→off
	//  4: green flash: green→off
	//  5: blue flash: blue→off
	//  6: cyan flash: cyan→off
	//  7: magenta flash: magenta→off
	//  8: yellow flash: yellow→off
	//  9: black: off
	// 10: hue cycle: red→yellow→green→cyan→blue→purple
	// 11: mood light: random hue→random hue
	// 12: virtual candle: random yellows
	// 13: water reflections: random blues
	// 14: old neon: random orangeish reds
	// 15: the seasons: spring colors→summer→fall→winter
	// 16: thunderstorm: random blues & purples→white flashes
	// 17: stop light: red→green→yellow
	// 18: morse code: S.O.S in white

    switch (_override_pattern_id) {
      case LED_SET_COLOUR_PATTERN_OFF:
      {
        uint8_t stop_script[] = {'o'};
        uint8_t stop_script_result = hal.i2c->write(BLINKMLED_ADDRESS, sizeof(stop_script), &stop_script[0]);
        uint8_t black_now[] = { 'n', 0, 0, 0 };
        uint8_t result = hal.i2c->write(BLINKMLED_ADDRESS, sizeof(black_now), &black_now[0]);
        break;
      }
      case LED_SET_COLOUR_PATTERN_SOLID:
      case LED_SET_COLOUR_PATTERN_FADEOUT:
      {
        uint8_t stop_script[] = {'o'};
        uint8_t stop_script_result = hal.i2c->write(BLINKMLED_ADDRESS, sizeof(stop_script), &stop_script[0]);
      }
      default:
        break;
    }

    // give back i2c semaphore
    i2c_sem->give();

    return _override_pattern_id;
}

// handle a LED_SET_COLOUR message
void BlinkMLED_I2C::handle_led_set_colour(mavlink_message_t *msg)
{
    // decode mavlink message
    mavlink_led_set_colour_t packet;
    mavlink_msg_led_set_colour_decode(msg, &packet);
    // hal.console->print_P(PSTR("\nhandle_led_set_colour:"));
    // hal.console->print_P(PSTR("\ninstance_id: "));
    // hal.console->print(packet.instance_id);
    // hal.console->print_P(PSTR("\npattern: "));
    // hal.console->print(packet.pattern);
    // hal.console->print_P(PSTR("\nred: "));
    // hal.console->print(packet.red);
    // hal.console->print_P(PSTR("\ngreen: "));
    // hal.console->print(packet.green);
    // hal.console->print_P(PSTR("\nblue: "));
    // hal.console->print(packet.blue);

    // exit immediately if instance is invalid
    if (packet.instance_id >= BLINKMLED_NUM_INSTANCES && packet.instance_id != BLINKMLED_ALL_INSTANCES) {
        hal.console->print_P(PSTR("\nInvaild Instance ID\n"));
        return;
    }

    set_override_pattern(packet.pattern);
    set_rgb(packet.red, packet.green, packet.blue);
}

// Overriding update() - updates led according to timed_updated. Should be called at 50Hz.
// Not implemented yet. This is only needed when using BlinkM as the status LED.
void BlinkMLED_I2C::update()
{
    // return immediately if not enabled
    if (!_healthy) {
        return;
    }

    // from ardupilotmega.h defined in mavlink
    // LED_SET_COLOUR_PATTERN_OFF=0, // LED patterns off (return control to regular vehicle notification and status indicator)
    // LED_SET_COLOUR_PATTERN_SINE=1, // LED Solid pattern
    // LED_SET_COLOUR_PATTERN_SOLID=2, // LED Solid pattern
    // LED_SET_COLOUR_PATTERN_SIREN=3, // LED Siren pattern
    // LED_SET_COLOUR_PATTERN_STROBE=4, // LED Strobe pattern
    // LED_SET_COLOUR_PATTERN_FADEIN=5, // LED Fade-in pattern
    // LED_SET_COLOUR_PATTERN_FADEOUT=6, // LED Fade-out pattern
    // LED_SET_COLOUR_PATTERN_CUSTOM=255, // Custom Pattern using custom bytes fields
    switch (_override_pattern_id) {
      case LED_SET_COLOUR_PATTERN_OFF:
      {
        break;
      }
      case LED_SET_COLOUR_PATTERN_SINE:
        break;

      case LED_SET_COLOUR_PATTERN_SOLID:
        // Just use rgb values manually set before calling update()
        break;

      case LED_SET_COLOUR_PATTERN_SIREN:
        break;

      case LED_SET_COLOUR_PATTERN_STROBE:
        break;

      case LED_SET_COLOUR_PATTERN_FADEIN:
        break;

      case LED_SET_COLOUR_PATTERN_FADEOUT:
      {
        break;
      }
      case LED_SET_COLOUR_PATTERN_CUSTOM:
        break;

      default:
        break;
    }
}

