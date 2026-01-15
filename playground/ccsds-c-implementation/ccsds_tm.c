/**
 * @author Edwin Mwiti 
 * emwiti658@gmail.com
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ccsds_tm.h"

char* mission_id = "PSF_ADVENT_1";
uint32_t spacecraft_id = 26001001; // YYXXXAA -> see telemetry packet diagram
uint8_t craft_id = 100; // to fit into 10 bit value

/* create CCDS packet struct */
CCSDS_packet* CCSDS_packet_create() {
    CCSDS_packet* pkt = (CCSDS_packet*) malloc(sizeof(CCSDS_packet));

    if(pkt != NULL) {
        CCSDS_packet_init(
            pkt, 
            CCSDS_packet_set_spacecraft_id,
            CCSDS_packet_get_spacecraft_id,
            CCSDS_packet_create_transfer_frame_primary_header,
            CCSDS_packet_create_transfer_frame_secondary_header,
            CCSDS_packet_extract_packet_primary_header,
            CCSDS_packet_dump_metadata,
            CCSDS_packet_telemetry_faker,
            CCSDS_packet_telemetry_cleanup,
            CCSDS_packet_print_bin
        );

    }
}

/* call init with the created functions */
void CCSDS_packet_init(
    CCSDS_packet* p,
    void (*CCSDS_packet_set_spacecraft_id)(CCSDS_packet*, uint32_t),
    uint32_t (*CCSDS_packet_get_spacecraft_id)(CCSDS_packet*), 
    void (*CCSDS_packet_create_transfer_frame_primary_header)(CCSDS_packet*),
    void (*CCSDS_packet_create_transfer_frame_secondary_header)(CCSDS_packet*),
    void (*CCSDS_packet_extract_packet_primary_header)(CCSDS_packet*),
    void (*CCSDS_packet_dump_metadata)(CCSDS_packet*),
    void (*CCSDS_packet_telemetry_faker)(CCSDS_packet* p),
    void (*CCSDS_packet_cleanup)(CCSDS_packet*),
    void (*CCSDS_packet_print_bin)(int)
) {
    if(p != NULL ){

        p->version_number = VERSION_NUMBER;
        p->spacecraft_id = craft_id;
        strncpy(p->mission_id, mission_id, strlen(mission_id) + 1);

        // assign function pointer objects 
        p->_CCSDS_packet_set_spacecraft_id = CCSDS_packet_set_spacecraft_id;
        p->_CCSDS_packet_get_spacecraft_id = CCSDS_packet_get_spacecraft_id;
        p->_CCSDS_packet_create_transfer_frame_primary_header = CCSDS_packet_create_transfer_frame_primary_header;
        p->_CCSDS_packet_create_transfer_frame_secondary_header = CCSDS_packet_create_transfer_frame_secondary_header,
        p->_CCSDS_packet_extract_packet_primary_header = CCSDS_packet_extract_packet_primary_header;
        p->_CCSDS_packet_cleanup = CCSDS_packet_cleanup;
        p->_CCSDS_packet_dump_metadata = CCSDS_packet_dump_metadata;
        p->_CCSDS_packet_telemetry_faker = CCSDS_packet_telemetry_faker;
        p->_CCSDS_packet_print_bin = CCSDS_packet_print_bin;

        /* initialize defaults packet headers according to CCSDS protocol */
        p->version_number = VERSION_NUMBER;
        p->transfer_frame_primary_header = 0x00;

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

/**
 * @brief Create the transfer frame primary header 
 */
void CCSDS_packet_create_transfer_frame_primary_header(CCSDS_packet* p) {
    /* package the version number */
    uint8_t v_num = 0x00;
    v_num |= VERSION_NUMBER;

    /* package the craft ID */
    uint16_t id = 0x00;
    id |= ( (id >> 6) | (craft_id));

    /* package the virtual channel ID, op control flag, master channel frame count and virtual channel frame count */
    uint8_t virtual_channel_id = 0x00;
    uint8_t op_control_flag = 0x00;
    uint8_t master_channel_frame_count = 0x00;
    uint8_t virtual_channel_frame_count = 0x00; 
    
    /* set the transfer frame data field status to 0 -> can be packed later */
    #if TPFH_TRANSFER_FRAME_DATA_FIELD_STATUS_DISABLE
        uint64_t transfer_frame_data_status = 0x0000; // todo: optimize
    #endif
    
    /* final packaged primary header 0 -> primary header is the first 48 bits(from LSB) */
    p->transfer_frame_primary_header |= ( 
        (v_num) |                               // LSB
        (id << 2) | 
        (virtual_channel_id <<  12) | 
        (op_control_flag << 15) | 
        (master_channel_frame_count << 16) |
        (virtual_channel_frame_count << 24) |
        (transfer_frame_data_status << 32)
    );

    printf("version num: %d\n", v_num);
    printf("Craft ID: %d\n", id);
    //printf("TFPH:%d\n",  p->transfer_frame_primary_header);
}

/**
 * @brief create transfer frame secondary header
 * in this version, this header contains metadata about the data frame
 */
void CCSDS_packet_create_transfer_frame_secondary_header(CCSDS_packet* p) {
    uint32_t secondary_header = 0;
    uint8_t secondary_version_num = 0x00;
    uint8_t secondary_sync_flag = 0x00;
    uint16_t secondary_header_data_field = 0x0000;

    /* pack the header */
    secondary_header |= ( (secondary_version_num) | (secondary_sync_flag << 2) );

    /* get the length of data field  */
    // uint16_t data_len = p->_data_field_length;

    // if(data_len > CCSDS_MAX_PACKET_SIZE) {
    //     puts("Data field too long\r\n"); // todo: log
    // } else {
    //     secondary_header_data_field |= data_len;
    // }

    secondary_header |= (secondary_header_data_field << 8);

    // return ?
    
}

void CCSDS_packet_create_data_field(CCSDS_packet* p) {

}

/*============ generate dummy data ================== */
// generate EPS data
// this will come from the EPS board as a struct from an RTOS task
eps_data_t* generate_eps_fake(void) {
    eps_data_t* data = (eps_data_t*) malloc(sizeof(eps_data_t));

    if(data != NULL) {
        
    }


    return data;
}



// generate ADCS data
// generate EPS data 
// generate PAYLOAD data

/**
 * @brief extract primary header fields
 */
void CCSDS_packet_extract_packet_primary_header(CCSDS_packet* p) {
    uint8_t version = p->transfer_frame_primary_header & ( (1 << 1UL) | (1 << 0UL) );
    uint16_t cr_id = (p->transfer_frame_primary_header >> 2) & (0b1111111111);

    puts("\n===== Primary frame extracted data =======\n");
    printf("version num: %d\n", version);
    printf("spacecraft ID: %d\n", cr_id);
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

/**
 * @brief generate dummy telemetry data
 */ 
void CCSDS_packet_telemetry_faker(CCSDS_packet* p) {
    /*generate OBS data */
    uint32_t obs_timestamp = UINT32_MAX; // timestamp
    float obs_board_voltage = 3.3;       // board_voltage
    float obs_board_current = 250.5;     // board_current
    uint32_t obs_uptime = 45500;         // uptime in seconds
    uint8_t obs_reset_count = 10;        // number_of_resets

    /*generate ADCS data*/
    float adcs_x_acc = 0.3;
    float adcs_y_acc = 6.3;
    float adcs_z_acc = 0.3;

    /* generate COMMS data */
    /* generate PAYLOAD data */
    /* generate EPS data */
}

/**
 * @brief print integer in binary
 */
void CCSDS_packet_print_bin(int x) {
    int leading_zero; 

    if (x == 0) {
        puts("0\n");
        return;
    } else {
        for(int k = 32; k >= 0; k--) {
            int b = (x >> k) & 1;

            if(b == 1) {
                leading_zero = 0;
            }

            if(!leading_zero) {
                printf("%d", b);
            }  
        } 
    }

    puts("\n");
}