/*
 * @file state_machine.c
 *
 * @date Jul 7, 2026
 * @author edwin
 */

#include "state_machine.h"

payload_state_t payload_state = STATE_STANDBY;

/**
 * @brief Return the state as a char*
 */
const char* payload_state_to_name(payload_state_t state) {
	switch (state){
	case STATE_STANDBY:
		return "STATE_STANDBY";
		break;
	case STATE_NOMINAL_SNAP_CAPTURE:
		return "STATE_NOMINAL_SNAP_CAPTURE";
		break;
	case STATE_NOMINAL_CONTINOUS_CAPTURE:
		return "STATE_NOMINAL_CONTINOUS_CAPTURE";
		break;
	case STATE_FAULT:
		return "STATE_FAULT";
		break;
	case STATE_GROUND_OVERRIDE:
		return "STATE_GROUND_OVERRIDE";
		break;
	default:
		return "INVALID STATE. ABORT";
	}
}
