#include "trove.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <unistd.h>
// Find each individual file that should be indexed
// Add absolute pathname to array?

// dirName should be the absolute pathname of the root file
void findfiles(char* dirName) {
    DIR* dir = opendir(dirName);
    if (dir == NULL) {
        printf("%s: directory not found\n", dirName);
        exit(EXIT_FAILURE);
    }

    struct dirent* entity;

    entity = readdir(dir);
    while (entity != NULL) {
        struct stat stat_buffer;

        if (S_ISDIR(stat_buffer.st_mode)) {
            char newPath[100] = { 0 };
                strcat(newPath, dirName);
                strcat(newPath, "/");
                strcat(newPath, entity->d_name);
                printf("directory found: %s\n", newPath);
                findfiles(newPath);
        } else if (S_ISREG(stat_buffer.st_mode)) {
            printf("file found : %s\n", entity->d_name);
        }
        entity = readdir(dir);
    }
    
    closedir(dir);
}