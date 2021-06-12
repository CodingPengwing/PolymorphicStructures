
#include "util.h"

// Prints an error of the format "error: <error message>" and exits the
// program with a non-zero error code
void 
exit_with_error(char *error) 
{
    fprintf(stderr, "error: %s\n", error);
    exit(EXIT_FAILURE);
}

void
println(char *string)
{
    printf("%s\n", string);
}

// Checks the index to see if it's valid for the object's size
int 
check_index(size_t size, int index)
{
    if (index < 0 || index >= size) 
        return 0;
    return 1;
}

// Scans a line of input depending on the input_length parameter given
int
scan_line(char *line, size_t input_length) 
{
    size_t i = 0;

    if (fgets(line, input_length, stdin)) 
    {
        while (line[i]!= '\n') 
            i++;
        return i;
    }
    
    return EOF;
}

// Create a new copy of the given string.
char *
string_Copy(char *string) 
{
    if (string == NULL) exit_with_error("Error in string_Copy(): NULL input.");
    size_t len = strlen(string);
    // Malloc 1 extra byte for null byte
    char *new_string = (char *)malloc((len+1)*sizeof(char));
    assert(new_string);
    strncpy(new_string, string, len);
    new_string[len] = '\0';
    return new_string;
}

// Free a string
void 
string_Free(char *string) 
{
    free(string);
}
