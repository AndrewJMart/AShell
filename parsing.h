#ifndef PARSING_H 
#define PARSING_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char **parse_commands(char *input_buffer, int *number_commands);

char **parse_args(char *raw_command, int *arg_length, int *redirect_index);

#endif

