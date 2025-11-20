#include <stdlib.h>
#include <string.h>
#include "ccsds_tm.h"

void telemetry_generate_dummy(void)
{
    /*generate OBS data */
    uint32_t obs_timestamp = UINT32_MAX; // timestamp
    float obs_board_voltage = 3.3;       // board_voltage
    float obs_board_current = 250.5;     // board_current
    uint32_t obs_uptime = 45500;         // uptime in seconds
    uint8_t obs_reset_count = 10;        // number_of_resets

    /*generate EPS data */

    /*generate ADCS data*/
    float adcs_x_acc = 0.3;
    float adcs_y_acc = 6.3;
    float adcs_z_acc = 0.3;

    /*generate COMMS data */
    /*generate PAYLOAD data */
}