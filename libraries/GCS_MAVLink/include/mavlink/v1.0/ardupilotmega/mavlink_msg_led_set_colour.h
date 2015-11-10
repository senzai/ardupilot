// MESSAGE LED_SET_COLOUR PACKING

#define MAVLINK_MSG_ID_LED_SET_COLOUR 189

typedef struct __mavlink_led_set_colour_t
{
 uint8_t target_system; /*< System ID*/
 uint8_t target_component; /*< Component ID*/
 uint8_t instance_id; /*< Instance ID of the LED to modify. (Set this to 0xFF for all LEDs)*/
 uint8_t red; /*< Red Colour Value (0x00-0xFF)*/
 uint8_t green; /*< Green Colour Value (0x00-0xFF)*/
 uint8_t blue; /*< Blue Colour Value (0x00-0xFF)*/
 uint8_t pattern; /*< Pattern (see LED_SET_COLOUR_PATTERN enum)*/
} mavlink_led_set_colour_t;

#define MAVLINK_MSG_ID_LED_SET_COLOUR_LEN 7
#define MAVLINK_MSG_ID_189_LEN 7

#define MAVLINK_MSG_ID_LED_SET_COLOUR_CRC 255
#define MAVLINK_MSG_ID_189_CRC 255



#define MAVLINK_MESSAGE_INFO_LED_SET_COLOUR { \
	"LED_SET_COLOUR", \
	7, \
	{  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_led_set_colour_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_led_set_colour_t, target_component) }, \
         { "instance_id", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_led_set_colour_t, instance_id) }, \
         { "red", NULL, MAVLINK_TYPE_UINT8_T, 0, 3, offsetof(mavlink_led_set_colour_t, red) }, \
         { "green", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_led_set_colour_t, green) }, \
         { "blue", NULL, MAVLINK_TYPE_UINT8_T, 0, 5, offsetof(mavlink_led_set_colour_t, blue) }, \
         { "pattern", NULL, MAVLINK_TYPE_UINT8_T, 0, 6, offsetof(mavlink_led_set_colour_t, pattern) }, \
         } \
}


/**
 * @brief Pack a led_set_colour message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system System ID
 * @param target_component Component ID
 * @param instance_id Instance ID of the LED to modify. (Set this to 0xFF for all LEDs)
 * @param red Red Colour Value (0x00-0xFF)
 * @param green Green Colour Value (0x00-0xFF)
 * @param blue Blue Colour Value (0x00-0xFF)
 * @param pattern Pattern (see LED_SET_COLOUR_PATTERN enum)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_led_set_colour_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t target_system, uint8_t target_component, uint8_t instance_id, uint8_t red, uint8_t green, uint8_t blue, uint8_t pattern)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_LED_SET_COLOUR_LEN];
	_mav_put_uint8_t(buf, 0, target_system);
	_mav_put_uint8_t(buf, 1, target_component);
	_mav_put_uint8_t(buf, 2, instance_id);
	_mav_put_uint8_t(buf, 3, red);
	_mav_put_uint8_t(buf, 4, green);
	_mav_put_uint8_t(buf, 5, blue);
	_mav_put_uint8_t(buf, 6, pattern);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LED_SET_COLOUR_LEN);
#else
	mavlink_led_set_colour_t packet;
	packet.target_system = target_system;
	packet.target_component = target_component;
	packet.instance_id = instance_id;
	packet.red = red;
	packet.green = green;
	packet.blue = blue;
	packet.pattern = pattern;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LED_SET_COLOUR_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_LED_SET_COLOUR;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_LED_SET_COLOUR_LEN, MAVLINK_MSG_ID_LED_SET_COLOUR_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_LED_SET_COLOUR_LEN);
#endif
}

/**
 * @brief Pack a led_set_colour message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system System ID
 * @param target_component Component ID
 * @param instance_id Instance ID of the LED to modify. (Set this to 0xFF for all LEDs)
 * @param red Red Colour Value (0x00-0xFF)
 * @param green Green Colour Value (0x00-0xFF)
 * @param blue Blue Colour Value (0x00-0xFF)
 * @param pattern Pattern (see LED_SET_COLOUR_PATTERN enum)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_led_set_colour_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t target_system,uint8_t target_component,uint8_t instance_id,uint8_t red,uint8_t green,uint8_t blue,uint8_t pattern)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_LED_SET_COLOUR_LEN];
	_mav_put_uint8_t(buf, 0, target_system);
	_mav_put_uint8_t(buf, 1, target_component);
	_mav_put_uint8_t(buf, 2, instance_id);
	_mav_put_uint8_t(buf, 3, red);
	_mav_put_uint8_t(buf, 4, green);
	_mav_put_uint8_t(buf, 5, blue);
	_mav_put_uint8_t(buf, 6, pattern);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LED_SET_COLOUR_LEN);
#else
	mavlink_led_set_colour_t packet;
	packet.target_system = target_system;
	packet.target_component = target_component;
	packet.instance_id = instance_id;
	packet.red = red;
	packet.green = green;
	packet.blue = blue;
	packet.pattern = pattern;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LED_SET_COLOUR_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_LED_SET_COLOUR;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_LED_SET_COLOUR_LEN, MAVLINK_MSG_ID_LED_SET_COLOUR_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_LED_SET_COLOUR_LEN);
#endif
}

/**
 * @brief Encode a led_set_colour struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param led_set_colour C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_led_set_colour_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_led_set_colour_t* led_set_colour)
{
	return mavlink_msg_led_set_colour_pack(system_id, component_id, msg, led_set_colour->target_system, led_set_colour->target_component, led_set_colour->instance_id, led_set_colour->red, led_set_colour->green, led_set_colour->blue, led_set_colour->pattern);
}

/**
 * @brief Encode a led_set_colour struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param led_set_colour C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_led_set_colour_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_led_set_colour_t* led_set_colour)
{
	return mavlink_msg_led_set_colour_pack_chan(system_id, component_id, chan, msg, led_set_colour->target_system, led_set_colour->target_component, led_set_colour->instance_id, led_set_colour->red, led_set_colour->green, led_set_colour->blue, led_set_colour->pattern);
}

/**
 * @brief Send a led_set_colour message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system System ID
 * @param target_component Component ID
 * @param instance_id Instance ID of the LED to modify. (Set this to 0xFF for all LEDs)
 * @param red Red Colour Value (0x00-0xFF)
 * @param green Green Colour Value (0x00-0xFF)
 * @param blue Blue Colour Value (0x00-0xFF)
 * @param pattern Pattern (see LED_SET_COLOUR_PATTERN enum)
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_led_set_colour_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, uint8_t instance_id, uint8_t red, uint8_t green, uint8_t blue, uint8_t pattern)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_LED_SET_COLOUR_LEN];
	_mav_put_uint8_t(buf, 0, target_system);
	_mav_put_uint8_t(buf, 1, target_component);
	_mav_put_uint8_t(buf, 2, instance_id);
	_mav_put_uint8_t(buf, 3, red);
	_mav_put_uint8_t(buf, 4, green);
	_mav_put_uint8_t(buf, 5, blue);
	_mav_put_uint8_t(buf, 6, pattern);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LED_SET_COLOUR, buf, MAVLINK_MSG_ID_LED_SET_COLOUR_LEN, MAVLINK_MSG_ID_LED_SET_COLOUR_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LED_SET_COLOUR, buf, MAVLINK_MSG_ID_LED_SET_COLOUR_LEN);
#endif
#else
	mavlink_led_set_colour_t packet;
	packet.target_system = target_system;
	packet.target_component = target_component;
	packet.instance_id = instance_id;
	packet.red = red;
	packet.green = green;
	packet.blue = blue;
	packet.pattern = pattern;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LED_SET_COLOUR, (const char *)&packet, MAVLINK_MSG_ID_LED_SET_COLOUR_LEN, MAVLINK_MSG_ID_LED_SET_COLOUR_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LED_SET_COLOUR, (const char *)&packet, MAVLINK_MSG_ID_LED_SET_COLOUR_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_LED_SET_COLOUR_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_led_set_colour_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t target_system, uint8_t target_component, uint8_t instance_id, uint8_t red, uint8_t green, uint8_t blue, uint8_t pattern)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint8_t(buf, 0, target_system);
	_mav_put_uint8_t(buf, 1, target_component);
	_mav_put_uint8_t(buf, 2, instance_id);
	_mav_put_uint8_t(buf, 3, red);
	_mav_put_uint8_t(buf, 4, green);
	_mav_put_uint8_t(buf, 5, blue);
	_mav_put_uint8_t(buf, 6, pattern);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LED_SET_COLOUR, buf, MAVLINK_MSG_ID_LED_SET_COLOUR_LEN, MAVLINK_MSG_ID_LED_SET_COLOUR_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LED_SET_COLOUR, buf, MAVLINK_MSG_ID_LED_SET_COLOUR_LEN);
#endif
#else
	mavlink_led_set_colour_t *packet = (mavlink_led_set_colour_t *)msgbuf;
	packet->target_system = target_system;
	packet->target_component = target_component;
	packet->instance_id = instance_id;
	packet->red = red;
	packet->green = green;
	packet->blue = blue;
	packet->pattern = pattern;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LED_SET_COLOUR, (const char *)packet, MAVLINK_MSG_ID_LED_SET_COLOUR_LEN, MAVLINK_MSG_ID_LED_SET_COLOUR_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LED_SET_COLOUR, (const char *)packet, MAVLINK_MSG_ID_LED_SET_COLOUR_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE LED_SET_COLOUR UNPACKING


/**
 * @brief Get field target_system from led_set_colour message
 *
 * @return System ID
 */
static inline uint8_t mavlink_msg_led_set_colour_get_target_system(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field target_component from led_set_colour message
 *
 * @return Component ID
 */
static inline uint8_t mavlink_msg_led_set_colour_get_target_component(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Get field instance_id from led_set_colour message
 *
 * @return Instance ID of the LED to modify. (Set this to 0xFF for all LEDs)
 */
static inline uint8_t mavlink_msg_led_set_colour_get_instance_id(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  2);
}

/**
 * @brief Get field red from led_set_colour message
 *
 * @return Red Colour Value (0x00-0xFF)
 */
static inline uint8_t mavlink_msg_led_set_colour_get_red(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  3);
}

/**
 * @brief Get field green from led_set_colour message
 *
 * @return Green Colour Value (0x00-0xFF)
 */
static inline uint8_t mavlink_msg_led_set_colour_get_green(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  4);
}

/**
 * @brief Get field blue from led_set_colour message
 *
 * @return Blue Colour Value (0x00-0xFF)
 */
static inline uint8_t mavlink_msg_led_set_colour_get_blue(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  5);
}

/**
 * @brief Get field pattern from led_set_colour message
 *
 * @return Pattern (see LED_SET_COLOUR_PATTERN enum)
 */
static inline uint8_t mavlink_msg_led_set_colour_get_pattern(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  6);
}

/**
 * @brief Decode a led_set_colour message into a struct
 *
 * @param msg The message to decode
 * @param led_set_colour C-struct to decode the message contents into
 */
static inline void mavlink_msg_led_set_colour_decode(const mavlink_message_t* msg, mavlink_led_set_colour_t* led_set_colour)
{
#if MAVLINK_NEED_BYTE_SWAP
	led_set_colour->target_system = mavlink_msg_led_set_colour_get_target_system(msg);
	led_set_colour->target_component = mavlink_msg_led_set_colour_get_target_component(msg);
	led_set_colour->instance_id = mavlink_msg_led_set_colour_get_instance_id(msg);
	led_set_colour->red = mavlink_msg_led_set_colour_get_red(msg);
	led_set_colour->green = mavlink_msg_led_set_colour_get_green(msg);
	led_set_colour->blue = mavlink_msg_led_set_colour_get_blue(msg);
	led_set_colour->pattern = mavlink_msg_led_set_colour_get_pattern(msg);
#else
	memcpy(led_set_colour, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_LED_SET_COLOUR_LEN);
#endif
}
