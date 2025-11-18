#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "parsing.h"
#include "execution.h"

int PATH_MAX = 1000;

int main() {
    while(1) {
        char cwd[PATH_MAX];

        getcwd(cwd, sizeof(cwd));

        char ashell_intro[] = "$ ";

        printf("%s%s", cwd, ashell_intro);

        size_t buffer_size = 5;

        char *input_buffer = (char *)malloc(sizeof(char) * buffer_size);

        // Collect Line From User
        getline(&input_buffer, &buffer_size, stdin);

        input_buffer[strcspn(input_buffer, "\n")] = '\0';

        // Rewrite All Tabs As Spaces
        int buffer_count = strlen(input_buffer);

        for (int char_pos = 0; char_pos != buffer_count; char_pos++) {
            if (input_buffer[char_pos] == '\t') {
                input_buffer[char_pos] = ' ';
            }
        } 

        // Parse Commands
        int num_commands;

        char **command_list = parse_commands(input_buffer, &num_commands);

        free(input_buffer);

        // Process Commands
        for (int i = 0; i != num_commands; i++) {
            int redirect_idx, arg_length;

            char **arg_list = parse_args(command_list[i], &arg_length, &redirect_idx);

            // Process Each Argument
            exec_args(arg_list, arg_length, redirect_idx);

            // Free Arg List
            for (int j = 0; j != arg_length; j++) {
            
                free(arg_list[j]);
            
            }

            free(arg_list);
        
        }

        // Free Command List
        for (int i = 0; i != num_commands; i++) {
            free(command_list[i]);
        }

        free(command_list);
    
    }
    
    return 0;
}
