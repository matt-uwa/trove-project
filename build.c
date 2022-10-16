#include "trove.h"

void build(char *pathName) {
    struct stat path;
    stat(pathName, &path);
    if (S_ISDIR(path.st_mode)) {
        findfiles(pathName);
    } else if (S_ISREG(path.st_mode)) {
        printf("FILE FOUND: %s\n", pathName);
    } else {
        printf("Could not locate directory or file named <%s>.\n", pathName);
    }
}