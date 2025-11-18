#include "parsing.h"

char **parse_commands(char *input_buffer, int *number_commands) {
    // Parse Through Initial Input Buffer For Commands

    // Create Pointe At Start Of Input Buffer
    char *input_pointer = input_buffer;

    // Create Next Token Pointer
    char *next_token;

    // Track Length Of How Many Commands
    int command_length = 0;

    // Initialize Initial Pointer To Hold All Command Pointers
    char **command_pointers = NULL;

    while ( (next_token = strsep(&input_pointer, "&")) != NULL) {
        // Reallocate Space For Another Pointer
        command_pointers = (char **)realloc(command_pointers, sizeof(char *) * (command_length + 1));

        // Add Next Token To Parsed Arguments
        command_pointers[command_length] = strdup(next_token);

        // Increment Command Length
        command_length++;
    }

    // Check If No Ampersand Found (Non Parallel Command)
    if (command_length == 0) {
    
        // Create Double Pointer That Contains Space For One Pointer
        command_pointers = (char **)malloc(sizeof(char *) * (command_length + 1));

        // Fill Single Pointer Space With Duplicated input_buffer
        command_pointers[0] = strdup(input_buffer);

        // Increment Command Length
        command_length++;
    }
    
    // Overwrite Passed In Pointer To "Return" Command Length For Main
    *number_commands = command_length;

    // Return List Of Pointers
    return command_pointers;

}

char **parse_args(char *raw_command, int *arg_length, int *redirect_tracker) {

        char *input_pointer = raw_command;

        char *next_token;

        int parse_length = 0;

        int redirect_index = 0;

        char **parse_pointers = NULL; 

        while ( (next_token = strsep(&input_pointer, " ")) != NULL) {
           // Skip Extra Spaces
           if (*next_token == 0) {
                continue;
           }
            
           // Reallocate Space For Another Pointer
           parse_pointers = (char **)realloc(parse_pointers, sizeof(char *) * (parse_length + 1));

           // Add Next Token To Parsed Arguments
           parse_pointers[parse_length] = strdup(next_token);

           // If redirect mark present 
           if (*next_token == '>') {

               redirect_index = parse_length;

           }

           parse_length++;

        }

        //add NULL pointer to end
        parse_pointers = (char **)realloc(parse_pointers, sizeof(char *) * (parse_length + 1));

        *redirect_tracker = redirect_index;
        *arg_length = parse_length;

        return parse_pointers; 
}
