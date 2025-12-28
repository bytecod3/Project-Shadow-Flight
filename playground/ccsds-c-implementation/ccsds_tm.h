/**
 * @author Edwin Mwiti
 * @brief This file declares the headers for CCSDS TM protocol
 */

 #ifndef CCSDS_TM_H
 #define CCSDS_TM_H

 #include <stdint.h>
 #include <stdlib.h>
 #include "data_types.h"

 /**
  * byte sizes 
  */
#define CCSDS_MAX_PACKET_SIZE (2000)
#define TRANSFER_FRAME_PRIMARY_HEADER_MAX_LENGTH   (6)
#define TRANSFER_FRAME_SECONDARY_HEADER_MAX_LENGTH (6)
#define TRANSFER_FRAME_DATA_FIELD_MAX_LENGTH (1024)
#define TRANSFER_FRAME_ERROR_CHECKSUM_MASK   (2)

/**
 * TRANSFER_FRAME_PRIMARY_HEADER (TFPH)
 */
#define TFPH_VERSION_NUMBER_MASK (0x03)
#define TFPH_SPACECRAFT_ID_MASK  (0X3FF)
#define TFPH_VIRTUAL_CHANNEL_ID_MASK    (0x07)
#define TFPH_OPERATIONAL_CONTROL_FLAG_MASK   (0x01)
#define TFPH_MASTER_CHANNEL_FRAME_COUNT_MASK (0xFF)
#define TFPH_VIRTUAL_CHANNEL_FRAME_COUNT_MASK (0xFF)
#define TPFH_TRANSFER_FRAME_DATA_FIELD_STATUS (0xFFFF)
#define TPFH_TRANSFER_FRAME_DATA_FIELD_STATUS_DISABLE (0x01)    ///< set to 0 to define transfer frame data field status

/**
 * transfer frame data field status (TF)
 * transfer frame secondary header status (TFSHS)
 */
#define TFSHS_FLAG_MASK (0x01)
#define TFSHS_SYNC_FLAG_MASK (0x01)
#define TFSHS_PACKET_ORDER_FLAG_MASK (0x01)
#define TFSHS_SEGMENT_LENGTH_ID_MASK (0x02)
#define TFSHS_FIRST_HEADER_POINTER_MASK (0x7FF)

/**
 * Transfer frame secondary header TFSH
 */
#define TFSH_ENABLE 0
#define TFSH_TRANSFER_FRAME_SECONDARY_HEADER_VERSION_NUMBER_MASK (0x02)
#define TFSH_SYNC_FLAG_MASK (0x3F)

#define TFSH_DATA_FIELD_MAX_LENGTH (64)

#define VERSION_NUMBER 0x01
extern char* mission_id;
extern uint32_t spacecraft_id; // YYXXXAA -> see telemetry packet diagram


/**
 * \brief faker function to generate dummy telemetry
 */
void telemetry_generate_dummy(void);


typedef struct CCSDS_packet CCSDS_packet;


/**
 * \brief Base class for CCSDS protocol
 */
struct CCSDS_packet {

    uint8_t version_number;
    uint16_t packet_size;
    char* mission_id;
    uint32_t spacecraft_id;

    /* packet */
    uint64_t transfer_frame_primary_header;
    uint8_t transfer_frame_version_number;

    /* member functions */
    void (*_CCSDS_packet_set_spacecraft_id)(CCSDS_packet*, uint32_t);
    uint32_t (*_CCSDS_packet_get_spacecraft_id)(CCSDS_packet*);

    // consolidation functions 
    void (*_CCSDS_packet_create_transfer_frame_primary_header)(CCSDS_packet*);
    void (*_CCSDS_packet_create_transfer_frame_data_status)(CCSDS_packet*);
    void (*_CCSDS_packet_create_transfer_frame_secondary_header)(CCSDS_packet*);


    // extraction functions 
    void (*_CCSDS_packet_extract_packet_primary_header)(CCSDS_packet*);
    void (*_CCSDS_packet_extract_data_field_status)(CCSDS_packet*);
    void (*_CCSDS_packet_extract_transfer_frame_seconday_header)(CCSDS_packet*);
    void (*CCSDS_packet_extract_transfer_frame_data_field)(CCSDS_packet*);
    void (*_CCSDS_packet_dump_metadata)(CCSDS_packet*);
    void (*_CCSDS_packet_telemetry_faker)(CCSDS_packet*);
    void (*_CCSDS_packet_cleanup)(CCSDS_packet*);
    void (*_CCSDS_packet_print_bin)(int);
};

/* member function prototypes */
CCSDS_packet *CCSDS_packet_create();
void CCSDS_packet_set_spacecraft_id(CCSDS_packet* p, uint32_t);
uint32_t CCSDS_packet_get_spacecraft_id(CCSDS_packet* p);

/* packet creation functions prototypes */
void CCSDS_packet_create_transfer_frame_primary_header(CCSDS_packet*);
void CCSDS_packet_create_transfer_frame_secondary_header(CCSDS_packet*);

/* packet data extraction functions */
void CCSDS_packet_extract_packet_primary_header(CCSDS_packet*);

/* member data simulation functions */
void CCSDS_packet_telemetry_faker(CCSDS_packet* p);
void CCSDS_packet_dump_metadata(CCSDS_packet* p);
void CCSDS_packet_cleanup_function (CCSDS_packet* p);
void CCSDS_packet_telemetry_cleanup(CCSDS_packet* p);

/* utility functions */
void CCSDS_packet_print_bin();

void CCSDS_packet_init(
    CCSDS_packet* p, 
    void (*_CCSDS_packet_set_spacecraft_id)(CCSDS_packet*, uint32_t),
    uint32_t (*_CCSDS_packet_get_spacecraft_id)(CCSDS_packet*), 
    void (*_CCSDS_packet_create_transfer_frame_primary_header)(CCSDS_packet*),
    void (*_CCSDS_packet_create_transfer_frame_secondary_header)(CCSDS_packet*),
    void (*_CCSDS_packet_extract_packet_primary_header)(CCSDS_packet*),
    void (*_CCSDS_packet_dump_metadata)(CCSDS_packet*),
    void (*_CCSDS_packet_telemetry_faker)(CCSDS_packet*),
    void (*_CCSDS_packet_cleanup)(CCSDS_packet*),
    void (*_CCSDS_packet_print_bin)(int x)
);

#endif