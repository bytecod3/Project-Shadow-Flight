/*
 *
 * @file ccsds_tm.c
 * @brief This file declares the headers for telemetry data link protocol under CCSDS
 * @date Oct 6, 2025
 * @author Edwin
 *
 */

#include "ccsds_tm.h"


/**
 * @fn uint16_t CCSDS_TM_calculate_crc16()
 * @brief This function calculates the CRC16 for the given sequence of bytes
 * @return crc16 value
 */
uint16_t CCSDS_TM_calculate_crc16(const uint8_t *data_buffer, uint16_t length) {

	uint16_t crc = 0xFFFF;

	for(uint16_t pos = 0; pos < length; pos++) {
		crc ^= (uint16_t) data_buffer[pos];

		for(uint8_t i = 0; i< 8; i++) {
			if(crc & 0x0001){
				crc = (crc >> 1) ^ CRC_POLYNOMIAL;
			} else {
				crc >>= 1;
			}
		}

	}

	return crc;
}


