/*
 * @file settings.h
 *
 * @brief This file declares variables that can be turned ON and/or OFF to activate
 * or deactivate data filters
 *
 * @date Oct 8, 2025
 * @author eduh
 */

#ifndef INC_FILTER_CONFIG_H_
#define INC_FILTER_CONFIG_H_

/**
 * @defgroup filters_config Filter configuration flags
 * @brief compile-time flags for enabling or disabling various filtering algorithms
 *
 * set the following definitions to 1 to use that filter algorithm and 0 to disable it
 * You must use at least 1 filter algorithm
 *
 *@{
 */
#define USE_KALMAN_FILTER				(0)
#define USE_MEDIAN_FILTER				(1)
#define USE_MOVING_AVERAGE_FILTER		(0)
#define USE_EXTENDED_KALMAN_FILTER		(0)
#define USE_COMPLEMENTARY_FILTER		(0)

/** @}*/

#endif /* INC_FILTER_CONFIG_H_ */
