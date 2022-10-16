// header files required by all files
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <dirent.h>
#include <limits.h>

#define _GNU_SOURCE
#include <stdlib.h>
// global preprocessor constants

// global functions (only param type, no name)

extern void findfiles(char*);

// global variables (no data size)

// Stores the absolute pathname of the trovefile (default /tmp/trove)
extern char *trovePath;

// Minimum word length from -l flag
extern int minLength;

