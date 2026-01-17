/**
 * @brief command engine functions
 * @author Edwin M.
 */
#ifndef COMMAND_ENGINE_H
#define COMMAND_ENGINE_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CMD_LENGTH          (255)

enum subsystems {
    OBC = 0,
    EPS,
    ADCU,
    COMMS,
    PAYLOAD
};

enum commands  {
    RESTART,
    SLEEP,
    GET_TIME,
    GET_STATE,
    SET_STATE,
    COMMS_ON,
    COMMS_OFF,
    PAYLOAD_ON,
    PAYLOAD_OFF
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
} sat_command_t;

/* caculate length of command before parsing */
uint16_t ce_get_cmd_length(const char* str);

/* check if the command intended is within the valid scope */
uint8_t ce_check_valid_command(const char* command);

/* how many tokens have been parsed */
size_t ce_get_token_count(char** tokens);

/* get the name of the command */
// const char* ce_get_command_name(command_type_t command);

/* check if target subsystem is valid */
uint8_t ce_check_valid_subsystem(const char* system);

/* check if time parsed as a parameter is valid*/
uint8_t ce_check_valid_time();

/* de-construct command into tokens */
char** ce_parse_command(sat_command_t c);

/* send to file system */
uint8_t ce_store_command_to_file(char* cmd);

#endif
