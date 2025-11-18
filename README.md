# AShell

AShell is a simple Unix-like shell implemented in C! After Reading through OS: 3 Easy Steps, I wanted to apply some of the knowledge I learned.

## Features

* Execute commands located in `/bin`
* Built-in `cd` command to change directories
* Built-in `exit` command to quit the shell
* Argument parsing and handling
* Output redirection using `>` operator
* Support for multiple commands separated by `&`
* Forking and process management for executing external commands

## File Structure

The project is organized as follows:

* `src/` contains the C source files
  * `AShell.c` main shell implementation
  * `execution.c` handles command execution and redirection
  * `parsing.c` handles parsing of input into commands and arguments
* `include/` contains header files
  * `execution.h`
  * `parsing.h`
* `bin/` contains the compiled shell executable
* `obj/` contains object files generated during compilation

## Compilation

To compile the shell, a Makefile is provided. Use the following command:

```bash
make
```

This will create the `bin/AShell` executable.

## Running the Shell

After compilation, you can start the shell by running:

```bash
make run
```

or directly:

```bash
./bin/AShell
```

## Usage

Type commands at the shell prompt `$`. Examples:

```bash
ls
cd /home/user
echo Hello > output.txt
```

## Cleaning the Build

To clean up compiled files and object files:

```bash
make clean
```

This will remove the `obj/` and `bin/` directories.
