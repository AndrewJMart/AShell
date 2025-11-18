

#ifndef EXECUTION_H 
#define EXECUTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

void exec_args(char **arg_list, int arg_length, int redirect_index);


#endif

