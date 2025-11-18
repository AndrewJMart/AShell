#include "execution.h"

void exec_args(char **arg_list, int arg_length, int redirect_index) {    
        
    // Check If Built In Command Exit
    if (strcmp(arg_list[0], "exit") == 0) {
        if (arg_length != 1) {
            printf("Invalid Command: Exit Command Takes 0 Args\n");

            // Return After Error
            return;
        }

        // Else Exit With No Error
        exit(0);
    }

    if (strcmp(arg_list[0], "cd") == 0) {
        if (arg_length == 1) {
           // Change System Path To Root
           chdir(getenv("HOME"));

           // Return After Error
           return;
        }
        if (arg_length == 2) {

           // Change System Path To New Dir
           chdir(arg_list[1]);

            // Return After Error
            return;
        }

        printf("Invalid Command: CD Command Takes 0 or 1 Arg\n");
        
        //Return After Error
        return;
    }

    // Not Built In Command
    char access_string[256] = "/bin/";

    strcat(access_string, arg_list[0]);

    // Check If First Argument Is Accessible
    int access_check = access(access_string, X_OK);

    if (access_check != 0) {

        printf("Invalid Command: Passed Command Is Not Accesible In Bin\n");
        
        // Return After Error
        return;

    }

    // Fork Process
    int p = fork();

    // In Child Process
    if (p == 0) {

        // Make Errors Go To STD_OUTPUT
        dup2(1, 2);

        // Check If Output Is Redirected Redirected
        if (redirect_index != 0) {

            // Check Passed Command Is Valid
            if (redirect_index + 2 != arg_length) {
                printf("Invalid Command: Redirect Syntax Is ... > file.txt");
                
                // Return After Error
                return;
            }

            // If Valid Set STD_OUT To File Chosen
            int fd = open(arg_list[redirect_index + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);

            dup2(fd, 1);

            close(fd);

            // Format Arguments Up To Redirect Index
            char **execv_args = malloc((redirect_index + 1) * sizeof(char *));

            for (int parse_args = 0; parse_args != redirect_index; parse_args++) {
                // Duplicate Arg Into ExecV Args
                execv_args[parse_args] = strdup(arg_list[parse_args]);
            }

            // Initialize NULL Pointer As Last Arg For Execv
            execv_args[redirect_index] = NULL;

            int error_code = execv(access_string, execv_args);
            fprintf(stderr, "execv failed: %s\n", strerror(errno));
        }

        // Not Redirected
        
        // Realloc with NULL at end
        arg_list = realloc(arg_list, arg_length * sizeof(char *));
        arg_list[arg_length] = NULL; 

        int error_code = execv(access_string, arg_list);
        
        fprintf(stderr, "execv failed: %s\n", strerror(errno)); 


    } else {

        wait(NULL);

    }

    // Have Parent Return
    return;
}
