#include <stdio.h>
#include "ccsds_tm.h"

int main() {
    
    CCSDS_packet* ccsds_tm;             // initialise CCSDS packet instance
    ccsds_tm = CCSDS_packet_create();

    ccsds_tm->_CCSDS_packet_dump_metadata(ccsds_tm);

    return 0;
}