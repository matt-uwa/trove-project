#include "trove.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <unistd.h>
// Find each individual file that should be indexed
// Add absolute pathname to array?

void recursiveCall(char *dirName) {
    struct dirent* entity;
    DIR* dir = opendir(dirName);
    if (dir == NULL) {
        printf("%s: error opening directory.\n", dirName);
        exit(EXIT_FAILURE);
    }
    entity = readdir(dir);
    while (entity != NULL) {
        if (entity->d_type == DT_DIR && strcmp(entity->d_name, ".") != 0 && strcmp(entity->d_name, "..") != 0) {
            char newPath[100] = { 0 };
            strcat(newPath, dirName);
            strcat(newPath, "/");
            strcat(newPath, entity->d_name);
            printf("DIRECTORY FOUND : %s\n", newPath);
            recursiveCall(newPath);
        } else if (entity->d_type == DT_REG) {
            char newPath[100] = { 0 };
            strcat(newPath, dirName);
            strcat(newPath, "/");
            strcat(newPath, entity->d_name);
            printf("FILE FOUND : %s\n", newPath);
        }
        entity = readdir(dir);
    }
    closedir(dir);
}
// dirName should be the absolute pathname of the root file
void findfiles(char* dirName) {
    struct stat path;
    stat(dirName, &path);
    if (S_ISDIR(path.st_mode)) {
        recursiveCall(dirName);
    } else if (S_ISREG(path.st_mode)) {
        printf("FILE FOUND: %s\n", dirName);
    } else {
        printf("Could not locate directory or file named <%s>.\n", dirName);
    }
}