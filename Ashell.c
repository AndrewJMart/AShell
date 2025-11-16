i#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    printf("\nHello I'm AShell!\n");

    // Test: Try Taking One Line Of User Input
    // Use Getline
    
    while(1) {
    
        size_t buffer_size = 5;

        char *input_buffer = (char *)malloc(sizeof(char) * buffer_size);

        // Collect Line From User
        getline(&input_buffer, &buffer_size, stdin);

        printf("You Typed: %s\n", input_buffer);

        // Now Parse Input Line For First Token
        
        // Ensure Input Buffer Still Points To Beginning Of String
        char *input_pointer = input_buffer;

        char *space_delim = " ";
        char *next_token = strsep(&input_pointer, space_delim);

        printf("Here Is First Token Found, %s\n", next_token);
        printf("Here Is Moved Past String, %s\n", input_pointer);

        free(input_buffer);
    }
    

    return 0;
}
