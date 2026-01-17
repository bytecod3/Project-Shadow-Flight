#include "stdio.h"
#include "command_engine.h"

int main() {
    /* use a modifiable memory location */
    char cmd[] = "EPS RESTART 2026-01-13 15:30:00";

    char** c = ce_parse_command(cmd);

    // print the tokens
    int h = ce_get_token_count(c);
    printf("%d\n", h);

    for(int i =0; i< h; i++) {

        puts(c[i]);
    }

    /* free the tokens memory */
    for (int i = 0; c[i]; ++i) {
        free(c[i]);
    }
    free(c);

    return 0;
}