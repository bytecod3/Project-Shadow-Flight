#include <stdio.h>
#include "ccsds_tm.h"

int main() {
    
    CCSDS_packet* ccsds_tm;             // initialise CCSDS packet instance
    ccsds_tm = CCSDS_packet_create();

    ccsds_tm->_CCSDS_packet_dump_metadata(ccsds_tm);

    /* test primary header frame creation and extraction */
    ccsds_tm->_CCSDS_packet_create_transfer_frame_primary_header(ccsds_tm);
    ccsds_tm->_CCSDS_packet_extract_packet_primary_header(ccsds_tm);

    return 0;
}