/*
 * @file ccsds_tm.h
 * @ brief This file declares the functions for CCSDS telemetry protocol
 * @author Edwin Mwiti
 * @date Oct 6, 2025
 *
 *
 */

#ifndef INC_CCSDS_TM_H_
#define INC_CCSDS_TM_H_

#include "stdio.h"
#include "defines.h"

#define CRC_POLYNOMIAL 0x1021    ///< Polynomial to use for CRC-16 calculation


/**
 * @fn uint16_t CCSDS_TM_calculate_crc16()
 * @brief This function calculates the CRC16 for the given sequence of bytes
 * @return crc16 value
 */
uint16_t CCSDS_TM_calculate_crc16(const uint8_t *data_buffer, uint16_t length);

/**
 * @fn void CCSDS_TM_compose_packet()
 * @brief This function creates a CCSDS packet based off the passed data
 *
 */
void CCSDS_TM_compose_packet();

/**
 * @fn void CCSDS_TM_parse_packet()
 * @brief This function decomposes a CCSDS packet
 *
 */
void CCSDS_TM_parse_packet();

#endif /* INC_CCSDS_TM_H_ */
