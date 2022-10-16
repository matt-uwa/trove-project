// header files required by all files
#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <dirent.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <unistd.h>
#include <stdlib.h>
// global preprocessor constants

// global functions (only param type, no name)

extern void findfiles(char*);
extern void build(char*);

// global variables (no data size)

// Stores the absolute pathname of the trovefile (default /tmp/trove)
// extern char *trovePath;

// Minimum word length from -l flag
extern int minLength;

