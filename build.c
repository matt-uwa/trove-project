#include "trove.h"

void build(char *pathName) {
    struct stat path;
    stat(pathName, &path);
    // checks if pathName corresponds to a file or directory
    if (S_ISDIR(path.st_mode)) {
        findfiles(pathName);
    } else if (S_ISREG(path.st_mode)) {
        // No need to recursively find all files since pathName is not a directory
        printf("FILE FOUND: %s\n", pathName);
        indexing(pathName);
    } else {
        printf("Could not locate directory or file named <%s>.\n", pathName);
    }
}