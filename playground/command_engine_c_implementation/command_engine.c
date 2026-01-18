/**
 * @brief This file implements command engine functions
 * @author Edwin M.
*/

#include "command_engine.h"

/**
 * @brief check for valid sub-system
 */
uint8_t ce_check_valid_subsystem(CommandEngine* inst, char* system) {
    if(inst == NULL) return 0;
    if(system == NULL) return 0;

    printf("validating subsystem...");

    uint8_t k = 0;
    uint8_t sys_valid = 0;
    while (inst->subsystems_tbl[k] != NULL) k++;

    uint8_t indx = 0;
    uint8_t system_offset = 0;

    /* linear search */
    for (indx; indx < k; indx++) {
        if (strcmp(system, inst->subsystems_tbl[indx]) == 0) {
            sys_valid = 1;
            system_offset = indx;
            break;
        }
    }

    if (sys_valid) {
        printf("Subsystem %s OK\n", system);
        return 1;
    } else {
        return 0;
    }
}

/**
 * @brief check if the command to be processed is valid
 * @param command
 * @return true is command is valid
 */
uint8_t ce_check_valid_command(CommandEngine* inst, char* cmd) {

    if(cmd == NULL) return 0;

    printf("Validating command...");

    /* perform a linear search for this command */
    uint8_t l = 0;
    uint8_t cmd_valid = 0;
    while(inst->commands_tbl[l] != NULL) l++;

    uint8_t cmd_index = 0;
    uint8_t command_offset = 0;
    for(cmd_index; cmd_index < l; cmd_index++) {
        if(strcmp(cmd, inst->commands_tbl[cmd_index]) == 0) {
            cmd_valid = 1;
            command_offset = cmd_index;
            break;
        }
    }

    if(cmd_valid) {
        printf("Command %s OK\n",cmd);
        return 1;
    } else {
        printf("Command does not exist\n", cmd);
        return 0;
    }

}

uint8_t ce_get_cmd_length(CommandEngine* inst, const char* str) {
    uint16_t len = 0;
    while(str[len] != '\0') len++;
    return len;
}

/* parse received command */
char** ce_tokenize(CommandEngine* inst, sat_command_t c) {

    /* check type of command */
    if (c.cmd_type == IMMEDIATE) {
        puts("Immediate command");
    } else if(c.cmd_type == SCHEDULED) {
        puts("scheduled command");
    }

    /* make a copy of this command */
    uint8_t cmd_len = inst->get_cmd_length(inst, c.cmd);
    char cmd_cpy[cmd_len + 1];
    strcpy(cmd_cpy, c.cmd);

    printf("Parsing cmd: %s\n", cmd_cpy);
    /* split the string using spaces */
    const char* dlm = " ";
    uint8_t args_count = 0;
    char* tmp = cmd_cpy;

    /* count the number of arguments to be extracted */
    uint8_t j = 0;
    while(tmp[j] != '\0') {
        if(tmp[j] == *dlm) {
            args_count++;
        }
        j++;
    }

    /* handle the last argument, 3 spaces == 4 arguments */
    args_count++;

    /* store these tokens somewhere */
    char** result = malloc(sizeof(char*) * (args_count+1));

    if(result != NULL) {
         size_t index = 0;
         char* token = strtok(cmd_cpy, dlm);
         while (token && index < args_count) {
             result[index] = strdup(token);
             token = strtok(NULL, dlm);
             index++;
         }

         result[index] = NULL;

         return result;
    } else {
        return NULL;
    }
}

/* process a single command */
void ce_process_tokens(CommandEngine* inst, char** tokens) {
    uint8_t is_system_valid = inst->check_valid_subsystem(inst, tokens[0]);
    uint8_t is_command_valid = inst->check_valid_command(inst, tokens[1]);

    if(is_system_valid && is_command_valid) {
        puts("command check done. Ready to process...");

        // TODO: depending on teh specific subsytem, send to its queue

    }

}


/* how many tokens have been extracted */
size_t ce_get_token_count(CommandEngine* inst, char** tokens) {
    if(tokens == NULL) return 0;
    uint8_t k = 0;

    while(tokens[k] != NULL ) {
        k++;
    }

    return k;
}

/**
 * @brief Free command allocation structure
 * @param cmd
 * @return
 */
 void ce_free_memory(CommandEngine* inst, char** c) {
     for(int i =0; c[i]; ++i){
         free(c[i]);
     }

     free(c);
 }

// const char* ce_command_get_command_name(const char* command) {
//     if(ce_check_valid_command(command)) {
//         switch (command) {
//             case RESTART:
//                 return "restart";
//
//             case SLEEP:
//                 return "sleep";
//
//             default:
//                 return "invalid"
//
//         }
//     }
// }

 /* store commands to file */
 uint8_t ce_store_command_to_file(CommandEngine* inst, char* cmd) {
    FILE * cmd_file = fopen("cmds.txt", "a");
    if(cmd_file == NULL) return 0;

    int a = fputs(cmd, cmd_file);
    int b = fputc('\n', cmd_file);

     if((a == EOF) || (b == EOF)) {
         puts("Failed to write to file");
         fclose(cmd_file);
         return 0;
     }

     puts("Command written to file");
     fclose(cmd_file);
     return 1;
}

/**
 * @brief initialize the command engine struct
 */
void command_engine_init(
        CommandEngine* inst,
        uint8_t (*_ce_check_valid_subsystem)(CommandEngine* inst, char* system),
        uint8_t (*_ce_check_valid_command)(CommandEngine* inst, char* cmd),
        uint8_t (*_ce_get_cmd_length)(CommandEngine* inst, const char* str),
        char** (*_ce_tokenize)(CommandEngine* inst, sat_command_t c),
        size_t (*_ce_get_token_count)(CommandEngine* inst, char** tokens),
        void (*_ce_free_memory)(CommandEngine* inst, char** c),
        uint8_t (*_ce_store_command_to_file)(CommandEngine* inst, char* cmd),
        void (*_ce_process_tokens)(CommandEngine* inst, char** c)
        )

        {

    /* initialize look up tables */
    inst->subsystems_tbl = subsystems_table;
    inst->commands_tbl = commands_table;

    /* initialize attributes */
    inst->max_command_length = 255;
    inst->max_response_length = 255;
    inst->max_num_of_commands = 255;

    /* assign arguments to this instance */
    inst->check_valid_subsystem = _ce_check_valid_subsystem;
    inst->check_valid_command = _ce_check_valid_command;
    inst->get_cmd_length = _ce_get_cmd_length;
    inst->tokenize = _ce_tokenize;
    inst->get_token_count = _ce_get_token_count;
    inst->free_memory = _ce_free_memory;
    inst->store_command_to_file = _ce_store_command_to_file;
    inst->process_tokens = _ce_process_tokens;

}


/**
 * @brief Create the command engine class
 */
CommandEngine* command_engine_create(void) {
    CommandEngine* inst = (CommandEngine*) malloc(sizeof(CommandEngine));
    if (inst == NULL) return NULL; // todo: return with log

    command_engine_init(
            inst,
            ce_check_valid_subsystem,
            ce_check_valid_command,
            ce_get_cmd_length,
            ce_tokenize,
            ce_get_token_count,
            ce_free_memory,
            ce_store_command_to_file,
            ce_process_tokens
            );

    return inst;
}