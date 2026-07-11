/*
 * state_machine.h
 *
 *  Created on: Jul 7, 2026
 *      Author: edwin
 */

#ifndef INC_STATE_MACHINE_H_
#define INC_STATE_MACHINE_H_

typedef enum payload_state_machine {
	STATE_STANDBY 						= 0,
	STATE_NOMINAL_SNAP_CAPTURE 			= 1,
	STATE_NOMINAL_CONTINOUS_CAPTURE 	= 2,
	STATE_FAULT							= 3,
	STATE_GROUND_OVERRIDE				= 4
} payload_state_t;

extern payload_state_t payload_state;

/**
 * @brief Return the state as a char*
 */
const char* payload_state_to_name(payload_state_t);

#endif /* INC_STATE_MACHINE_H_ */
