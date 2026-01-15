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

}

uint16_t ce_get_cmd_length(const char* str) {
    uint16_t len = 0;
    while(str[len] != '\0') len++;
    return len;
}

char** ce_parse_command(const char* cmd) {
    if(ce_check_valid_command(cmd) != 0) {
        /* split the string using spaces */
        const char dlm = ' '; 
        char* last_space = 0;
        char** args;
        uint8_t args_count = 0;
        char* tmp = cmd;
        char delim[2];
        delim[0] = dlm;
        delim[1] = 0;

        /* count the number of arguments to be extracted */
        while(*tmp) {
            if(dlm == *tmp) {
                args_count++;
                last_space = tmp;
            }
            tmp++;
        }

        /* handle the last argument, 3 spaces == 4 arguments */
        args_count++;

        /* store these tokens somewhere */
        char** result = malloc(sizeof(char) * args_count);

        if(result != NULL) {
            size_t index = 0;
            char* token = strtok(cmd, dlm);
            while (token) {
                *(result + index++) = strdup(token);
                token = strtok(NULL, dlm);
            }

            *(result + index) = 0;
            
        }

        return result;

    } else {
        /* failed to parse a null command*/
        return 0;
    }

}

// const char* ce_command_get_command_name(const char* command) {
//     if(ce_check_valid_command(command)) {
//         switch (command) {
//             case RESTART:
//                 return "restart";

//             case SLEEP:
//                 return "sleep";

//             default:
//                 return "invalid"

//         }
//     }
// }