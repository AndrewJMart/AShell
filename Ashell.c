#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("\nHello I'm AShell!\n");

    // Test: Try Taking One Line Of User Input
    // Use Getline
    char *input_buffer;
    size_t buffer_size = 5;

    input_buffer = (char *)malloc(sizeof(char) * buffer_size);

    // Collect Line From User
    getline(&input_buffer, &buffer_size, stdin);

    printf("You Typed: %s\n", input_buffer);
    
    return 0;
}
