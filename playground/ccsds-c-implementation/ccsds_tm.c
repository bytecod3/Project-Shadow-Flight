#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ccsds_tm.h"

/* create functions */
CCSDS_Packet *CCSDS_packet_create() {
    

}

/* call init with the created functions */
void CCSDS_packet_init(
    CCSDS_Packet* packet_inst, 
    void (*CCSDS_packet_set_spacecraft_id)(uint8_t),
    uint8_t (*CCSDS_packet_get_spacecraft_id), 
    void (*CCSDS_packet_telemetry_faker)(void),
    void (*CCSDS_packet_cleanup)(CCSDS_Packet*)
) {
    if(packet_inst != NULL ){
        packet_inst->_CCSDS_packet_set_spacecraft_id = CCSDS_packet_set_spacecraft_id;
        packet_inst->_CCSDS_packet_get_spacecraft_id = CCSDS_packet_get_spacecraft_id;

        packet_inst->_CCSDS_packet_cleanup = CCSDS_packet_cleanup;
        packet_inst->_CCSDS_packet_telemetry_faker = CCSDS_packet_telemetry_faker;

        packet_inst->version_number = 9;

    } else {
        puts("Packet instance is NULL");
    }
}

void CCSDS_packet_set_spacecraft_id(CCSDS_Packet* packet_inst, uint8_t id) {
    packet_inst->spacecraft_id;
}

uint8_t CCSDS_packet_get_spacecraft_id() {
    
}

/* destructor*/
void CCSDS_Packet_cleanup_function (CCSDS_Packet* packet) {
    if(packet != NULL) {
        free(packet);
    }
}

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