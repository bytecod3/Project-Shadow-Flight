/**
 * @brief This file implements command engine functions
 * @author Edwin M.
*/

#include "command_engine.h"

/**
 * @brief check if the command to be processed is valid
 * @param command
 * @return true is command is valid
 */
uint8_t ce_check_valid_command(const char* command) {
    return 1;
}

uint16_t ce_get_cmd_length(const char* str) {
    uint16_t len = 0;
    while(str[len] != '\0') len++;
    return len;
}

char** ce_parse_command(sat_command_t c) {

    /* check type of command */
    if (c.cmd_type == IMMEDIATE) {
        puts("Immediate command");
    } else if(c.cmd_type == SCHEDULED) {\
        puts("scheduled command");
    }

    if(ce_check_valid_command(c.cmd) != 0) {

        /* make a copy of this command */
        uint8_t cmd_len = ce_get_cmd_length(c.cmd);
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

             /* how many tokens do we have - reconfirm */
            //size_t tkn_count = ce_get_token_count(result);

             return result;
        } else {
            return NULL;
        }

    } else {
        /* failed to parse a null command*/
        return NULL;
    }

}

/* how many tokens have been extracted */
size_t ce_get_token_count(char** tokens) {
    if(tokens == NULL) return 0;
    uint8_t k = 0;

    while(tokens[k] != NULL ) {
        k++;
    }

    return k;
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
 uint8_t ce_store_command_to_file(char* cmd) {
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