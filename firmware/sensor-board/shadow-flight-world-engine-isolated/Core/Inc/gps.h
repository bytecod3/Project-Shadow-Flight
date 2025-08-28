/**
 *
 * @file gps.h
 * @brief This file contains GPS driver declarations
 * @author Edwin Mwiti
 * @date 28-08-2025
 *
 */


/**
 lat
 long
 altitude
 2d fix
 ground speed
 vertical speed
 heading over ground
 gps_time
 date(y/m/d)
 pps
 fix_status
 no_satelites
 no_os_solution_satelites
 elavation angle
 */

#ifndef INC_GPS_H_
#define INC_GPS_H_

#define GPS_USE_UART 1 /* set to 1 to activate GPS UART interface */
#define GPS_USE_I2C  0 /* set to 1 to activate GPS I2C interface */

#include "stm32f4xx_hal.h"
#include "stdint.h"
#include "string.h"



/**
 * @brief This struct defines the GPS data packet
 */
typedef struct gps_packet_type{
	float lat;								/*!< GPS latitude  */
	float lon;								/*!< GPS longitude  */
	float altitude;
	uint8_t fix; // check
	float ground_velocity;
	float vertical_speed;
	int heading;
	uint32_t gps_time;
	uint32_t date;
	uint8_t pps;
	uint8_t fix_status;
	uint8_t no_of_sats;
	uint8_t no_of_solution_satelites;
	float elevation_angle;
} gps_packet_type_t;

typedef gps_packet_type_t* gps_packet_ptr;

/**
 * @brief This function activates the GPS
 */
void GPS_activate(void );
void GPS_deactivate(void);
void GPS_reset(void);
void GPS_decode_NMEA(const char* packet);
void GPS_read_data();
void GPS_read_time();

#endif /* INC_GPS_H_ */


























