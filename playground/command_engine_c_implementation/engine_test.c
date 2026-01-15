#include "stdio.h"
#include "command_engine.h"

int main() {

    const char* cmd = "EPS RESTART 2026-01-13 15:30:00";

    ce_parse_command(cmd);

    //printf("%d\n", x);

    return 0;
}