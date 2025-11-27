/**
 * @brief This file declares the headers for CCSDS TM protocol
 */

 #ifndef CCSDS_TM_H
 #define CCSDS_TM_H

 #include <stdint.h>
 #include <stdlib.h>

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
#define TFSH_TRANSFER_FRAME_SECONDARY_HEADER_VERSION_NUMBER_MASK (0x02)
#define TFSH_SYNC_FLAG_MASK (0x3F)

#define TFSH_DATA_FIELD_MAX_LENGTH (64)

/**
 * \brief faker function to generate dummy telemetry
 */
void telemetry_generate_dummy(void);


typedef struct CCSDS_Packet CCSDS_Packet;


/**
 * \brief Base class for CCSDS protocol
 */
struct CCSDS_Packet {

    uint8_t version_number;
    uint16_t packet_size;
    uint8_t spacecraft_id;

    void (*_CCSDS_packet_set_spacecraft_id)(uint8_t);
    uint8_t (*_CCSDS_packet_get_spacecraft_id);
    
    void (*_CCSDS_packet_telemetry_faker)(void);
    void (*_CCSDS_packet_cleanup)(CCSDS_Packet*);

};

CCSDS_Packet *CCSDS_packet_create();


void CCSDS_packet_set_spacecraft_id(CCSDS_Packet* packet_inst, uint8_t);
void CCSDS_Packet_cleanup_function (CCSDS_Packet* packet_inst);
void CCSDS_Packet_telemetry_faker(CCSDS_Packet* packet_inst);

void CCSDS_packet_init(
    CCSDS_Packet* packet_inst, 
    void (*_CCSDS_packet_set_spacecraft_id)(uint8_t),
    uint8_t (*_CCSDS_packet_get_spacecraft_id), 
    void (*_CCSDS_packet_telemetry_faker)(void),
    void (*_CCSDS_packet_cleanup)(CCSDS_Packet*)
);

#endif