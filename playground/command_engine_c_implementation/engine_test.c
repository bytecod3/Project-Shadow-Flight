#include "stdio.h"
#include "command_engine.h"

int main() {

    /* use a modifiable memory location */
    char cmd[] = "EPS RESTART 2026-01-13 15:30:00";
    char cmd2[] = "COMMS SLEEP 2026-01-13 15:30:00";

    char** c = ce_parse_command(cmd);

    /* test -> store command to file */
    ce_store_command_to_file(cmd);
    ce_store_command_to_file(cmd2);

    /* free the tokens memory */
    for (int i = 0; c[i]; ++i) {
        free(c[i]);
    }

    free(c);

    return 0;
}