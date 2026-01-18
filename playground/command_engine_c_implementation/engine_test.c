#include "stdio.h"
#include "command_engine.h"

int main() {

    sat_command_t cmd1 = {
        IMMEDIATE,
        "COMMS ON"
    };

    sat_command_t cmd2 = {
            SCHEDULED,
            "COMMS RESTART 2026-01-13 15:30:00"
    };

    //char** c = ce_tokenize(cmd1);
//
//    // process tokens
//    ce_process_tokens(c);
//
//    /* free the tokens memory */
//    ce_free_memory(c);

    CommandEngine* cmd_engine = command_engine_create();
    char** tokens = cmd_engine->tokenize(cmd_engine, cmd2);

    cmd_engine->process_tokens(cmd_engine, tokens);

    cmd_engine->free_memory(cmd_engine, tokens);

    return 0;
}