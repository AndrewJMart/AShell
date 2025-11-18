#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "parsing.h"


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

        // Test Parsing.c
        int num_commands;

        char **command_list = parse_commands(input_buffer, &num_commands);

        printf("Number Of Commands: %d\n", num_commands);


        // Print Each Command
        for (int i = 0; i != num_commands; i++) {

            printf("Command %d: %s\n", i, command_list[i]);
        
        }

        for (int i = 0; i != num_commands; i++) {
        
            // Process Command
        
            int redirect_idx, arg_length;

            char **arg_list = parse_args(command_list[i], &arg_length, &redirect_idx);

            // Print Each Argument
            for (int j = 0; j != arg_length; j++) {
            
                printf("Arg %d: %s\n", j, arg_list[j]);
            
            }
        
        }

        exit(0);

        // Parse Input Line
        char *input_pointer = input_buffer;

        char *next_token;

        int parse_length = 0;

        int redirect_index = 0;

        char **parse_pointers = NULL; 

        while ( (next_token = strsep(&input_pointer, " ")) != NULL) {
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
        parse_pointers[parse_length] = NULL;

        //printf("Parsed Length: %d\n", parse_length);

        //for (int i = 0; i < parse_length; i++) {

            // Loop Through Parsed Arguments And Print
            //printf("Parsed Argument: %d, String: %s\n", i, parse_pointers[i]);
        
        //}

        // Check If Built In Command Exit
        if (strcmp(parse_pointers[0], "exit") == 0) {
            if (parse_length != 1) {
                printf("Invalid Command: Exit Command Takes 0 Args\n");
                free(input_buffer);
                // Free Parse_Pointers & Each Pointer
            
            } else {
                
                // Free Stuff
                exit(0);

            }
        }

        if (strcmp(parse_pointers[0], "cd") == 0) {
            if (parse_length == 1) {
               // Change System Path To Root
               chdir(getenv("HOME"));

               // Free Memory
               
               continue;
            }
            if (parse_length == 2) {
            
               // Change System Path To New Dir
               chdir(parse_pointers[1]);
               
                // Free Memory
                continue;
            }

            printf("Invalid Command: CD Command Takes 0 or 1 Arg\n");
            //Free Memory
            continue;
        }

        char access_string[256] = "/bin/";

        strcat(access_string, parse_pointers[0]);

        //printf("%s", access_string);

        // Check If First Argument Is Accessible
        int access_check = access(access_string, X_OK);
        
        if (access_check != 0) {
        
            printf("Invalid Command: Passed Command Is Not Accesible In Bin\n");
            free(input_buffer);
            continue;

        }


        // Fork Process    
        int p = fork();

        // In Child Process
        if (p == 0) {
            // Check If Redirected
            if (redirect_index != 0) {
                
                // Check Passed Command Is Valid
                if (redirect_index + 2 != parse_length) {
                    printf("%d\n", redirect_index);
                    printf("%d\n", parse_length);
                    printf("Invalid Command: Redirect Syntax Is ... > file.txt");
                    // Free Memory
                    exit(1);
                }
                
                // If Valid Set STD_OUT To File Chosen
                int fd = open(parse_pointers[redirect_index + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);

                dup2(fd, 1);
            
                close(fd);

                // Format Arguments Up To Redirect Index
                char **execv_args = malloc(redirect_index * sizeof(char *));
                
                for (int parse_args = 0; parse_args != redirect_index; parse_args++) {
                    // Duplicate Arg Into ExecV Args
                    execv_args[parse_args] = strdup(parse_pointers[parse_args]);
                }

                // Initialize NULL Pointer As Last Arg For Execv
                execv_args[redirect_index] = NULL;
                
                execv(access_string, execv_args);
            }
            
            // Not Redirected
            execv(access_string, parse_pointers);

        } else {
        
            wait(NULL);

        }

        free(input_buffer);
    }
    
    return 0;
}
