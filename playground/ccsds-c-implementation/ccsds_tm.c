/**
 * @author Edwin Mwiti emwiti658@gmail.com
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ccsds_tm.h"

char* mission_id = "PSF_ADVENT_1";
uint32_t spacecraft_id = 26001001; // YYXXXAA -> see telemetry packet diagram


/* create CCDS packet struct */
CCSDS_packet* CCSDS_packet_create() {
    CCSDS_packet* pkt = (CCSDS_packet*) malloc(sizeof(CCSDS_packet));

    if(pkt != NULL) {
        CCSDS_packet_init(
            pkt, 
            CCSDS_packet_set_spacecraft_id,
            CCSDS_packet_get_spacecraft_id,
            CCSDS_packet_dump_metadata,
            CCSDS_packet_telemetry_faker,
            CCSDS_packet_telemetry_cleanup
        );

    }
}

/* call init with the created functions */
void CCSDS_packet_init(
    CCSDS_packet* p, 
    void (*CCSDS_packet_set_spacecraft_id)(CCSDS_packet*, uint32_t),
    uint32_t (*CCSDS_packet_get_spacecraft_id)(CCSDS_packet*), 
    void (*CCSDS_packet_dump_metadata)(CCSDS_packet*),
    void (*CCSDS_packet_telemetry_faker)(CCSDS_packet* p),
    void (*CCSDS_packet_cleanup)(CCSDS_packet*)
) {
    if(p != NULL ){

        p->version_number = VERSION_NUMBER;
        p->spacecraft_id = spacecraft_id;
        strncpy(p->mission_id, mission_id, strlen(mission_id) + 1);

        // assign function pointer objects 
        p->_CCSDS_packet_set_spacecraft_id = CCSDS_packet_set_spacecraft_id;
        p->_CCSDS_packet_get_spacecraft_id = CCSDS_packet_get_spacecraft_id;
        p->_CCSDS_packet_dump_metadata = CCSDS_packet_dump_metadata;
        p->_CCSDS_packet_cleanup = CCSDS_packet_cleanup;
        p->_CCSDS_packet_telemetry_faker = CCSDS_packet_telemetry_faker;

        p->version_number = 9;

    } else {
        // only for embedded todo: log to logger on MCU
        puts("packet instance is NULL");
    }
}

/* set the spacecraft ID in case there is need to change */
void CCSDS_packet_set_spacecraft_id(CCSDS_packet* p, uint32_t id) {
    p->spacecraft_id = id;
}

/* get spacecraft ID*/
uint32_t CCSDS_packet_get_spacecraft_id(CCSDS_packet* p) {
    return p->spacecraft_id;
}

/* destructor*/
void CCSDS_packet_telemetry_cleanup(CCSDS_packet* p) {
    if(p != NULL) {
        free(p);
    }
}

/* print the spacecraft metadata */
void CCSDS_packet_dump_metadata(CCSDS_packet* p) {
    char metadata[256];

    sprintf(metadata, 
        "\r\nSpacecraft ID: %u\nMission ID: %s\r\n", 
        p->spacecraft_id,
        p->mission_id
    );

    puts(metadata);
}

/* generates dummy test data */
void CCSDS_packet_telemetry_faker(CCSDS_packet* p) {
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