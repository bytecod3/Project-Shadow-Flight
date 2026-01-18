/**
 * @brief command engine functions
 * @author Edwin M.
 */
#ifndef COMMAND_ENGINE_H
#define COMMAND_ENGINE_H

#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CMD_LENGTH                  (255)
#define MAX_CMD_RESPONSE_LENGTH          (255)

/* available sub systems  */
static const char* subsystems_table[] = {
    "OBC",
    "COMMS",
    "EPS",
    "ADCU",
    "PAYLOAD"
};

/* lookup table to store available internal commands */
static const char* commands_table[] = {
        "RESTART",
        "SLEEP",
        "GET_TIME",
        "GET_STATE",
        "SET_STATE",
        "ON",
        "OFF"
};

/* holds the type of command */
typedef enum _command_type {
    IMMEDIATE,
    SCHEDULED
} command_type_t;

/* represents a command type */
typedef struct  {
    command_type_t cmd_type;
    char cmd[MAX_CMD_LENGTH];
    char cmd_response[MAX_CMD_RESPONSE_LENGTH];
} sat_command_t;

/* pointer to satellite command */
typedef sat_command_t* sat_command_ptr;

typedef struct command_engine CommandEngine;

/**
 * @brief Create the command engine class
 */
CommandEngine* command_engine_create(void);

struct command_engine {
    /* lookup tables */
    const char** subsystems_tbl;
    const char** commands_tbl;

    /* command attributes */
    uint8_t max_command_length;
    uint8_t max_response_length;
    uint8_t max_num_of_commands;

    /* methods */
    uint8_t (*check_valid_subsystem)(CommandEngine* inst, char* system);
    uint8_t (*check_valid_command)(CommandEngine* inst, char* cmd);
    uint8_t (*get_cmd_length)(CommandEngine* inst, const char* str);
    char** (*tokenize)(CommandEngine* inst, sat_command_t c);
    size_t (*get_token_count)(CommandEngine* inst, char** tokens);
    void (*free_memory)(CommandEngine* inst, char** c);
    uint8_t (*store_command_to_file)(CommandEngine* inst, char* cmd);
    void (*process_tokens)(CommandEngine* inst, char** c);

};

/**
 * @brief Initialize command engine
 */
void command_engine_init(
        CommandEngine* inst,
        uint8_t (*_ce_check_valid_subsystem)(CommandEngine* inst,char* system),
        uint8_t (*_ce_check_valid_command)(CommandEngine* inst, char* cmd),
        uint8_t (*_ce_get_cmd_length)(CommandEngine* inst, const char* str),
        char** (*_ce_tokenize)(CommandEngine* inst,sat_command_t c),
        size_t (*_ce_get_token_count)(CommandEngine* inst, char** tokens),
        void (*_ce_free_memory)(CommandEngine* inst,char** c),
        uint8_t (*ce_store_command_to_file)(CommandEngine* inst,char* cmd),
        void (*_ce_process_tokens)(CommandEngine* inst,char** c)
);



/* calculate length of command before parsing */
uint8_t ce_get_cmd_length(CommandEngine* inst, const char* str);

/* check if the command intended is within the valid scope */
uint8_t ce_check_valid_command(CommandEngine* inst, char* command);

/* how many tokens have been parsed */
size_t ce_get_token_count(CommandEngine* inst, char** tokens);

/* free allocated memory */
void ce_free_memory(CommandEngine* inst, char** c);

/* get the name of the command */
// const char* ce_get_command_name(command_type_t command);

/* check if target subsystem is valid */
uint8_t ce_check_valid_subsystem(CommandEngine* inst, char* system);

/* check if time parsed as a parameter is valid*/
uint8_t ce_check_valid_time(CommandEngine* inst);

/* parse a single command */
void ce_parse_command(CommandEngine* inst, char* cmd);

/* de-construct command into tokens */
char** ce_tokenize(CommandEngine* inst, sat_command_t c);

/* process a single command */
void ce_process_tokens(CommandEngine* inst, char** c);

/* send to file system */
uint8_t ce_store_command_to_file(CommandEngine* inst, char* cmd);

#endif
