#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


int main() {
    printf("\nHello, I'm AShell!\n");
    while(1) {
    
        printf("AShell> ");
        size_t buffer_size = 5;

        char *input_buffer = (char *)malloc(sizeof(char) * buffer_size);

        // Collect Line From User
        getline(&input_buffer, &buffer_size, stdin);

        input_buffer[strcspn(input_buffer, "\n")] = '\0';

        // Parse Input Line
        char *input_pointer = input_buffer;

        char *next_token;

        int parse_length = 0;

        char **parse_pointers = NULL; 

        while ( (next_token = strsep(&input_pointer, " ")) != NULL) {
           // Reallocate Space For Another Pointer
           parse_pointers = (char **)realloc(parse_pointers, sizeof(char *) * (parse_length + 1));

           // Add Next Token To Parsed Arguments
           parse_pointers[parse_length] = strdup(next_token);

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
                printf("Invalid Command");
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

            printf("Invalid Argument");
            //Free Memory
            continue;
        }

        char access_string[256] = "/bin/";

        strcat(access_string, parse_pointers[0]);

        //printf("%s", access_string);

        // Check If First Argument Is Accessible
        int access_check = access(access_string, X_OK);
        
        if (access_check != 0) {
        
            printf("Invalid Command\n");
            free(input_buffer);
            continue;

        }


        // Fork Process    
        int p = fork();

        // In Child Process
        if (p == 0) {
            execv(access_string, parse_pointers);
            exit(0);

        } else {
        
            wait(NULL);

        }

        free(input_buffer);
    }
    

    return 0;
}
