/*
 * @file ntc.h
 * @brief driver for NTC temperature sensor
 * @author edwin
 */

#ifndef NTC_NTC_H_
#define NTC_NTC_H_

#define DEGREES_C_EN	0	/* set to 1 to convert to degrees C - default */
#define DEGREES_F_EN	0   /* set to 1 to convert to degrees F */

/**
 * @brief initialize NTC temperature sensor
 */
void ntc_init(void);

/**
 * @brief get raw temperature reading
 */
float ntc_read_raw_temperature(void);

/**
 * @brief convert temperature to either degrees C or Faren-heit
 */
float ntc_convert_tempeerature(uint8_t units);

#endif /* NTC_NTC_H_ */
