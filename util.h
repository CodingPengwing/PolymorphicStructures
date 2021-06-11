#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#ifndef UTIL_H
#define UTIL_H

// Prints an error of the format "error: <error message>" and exits the
// program with a non-zero error code
void 
exit_with_error(char *error);

void
println(char *string);

// Checks the index to see if it's valid for the object's size
int 
check_index(size_t size, int index);

// Scans a line of input depending on the input_length parameter given
int
scan_line(char *line, size_t input_length);

// Create a new string
char *
string_Create(size_t length);

// Free a string
void 
string_Free(char *string);

#endif
