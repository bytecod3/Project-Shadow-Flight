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
#include "commands.h"

/* caculate length of command before parsing */
uint16_t ce_get_cmd_length(const char* str);

/* check if the command intended is within the valid scope */
uint8_t ce_check_valid_command(const char* command);

/* get the name of the command */
// const char* ce_get_command_name(command_type_t command);

/* check if target subsystem is valid */
uint8_t ce_check_valid_subsystem(const char* system);

/* check if time parsed as a paramter is valid*/
uint8_t ce_check_valid_time();

/* de-construct commmand into tokens */
char** ce_parse_command(const char* c);

/* send to file system */
void ce_send_to_fs();

#endif
